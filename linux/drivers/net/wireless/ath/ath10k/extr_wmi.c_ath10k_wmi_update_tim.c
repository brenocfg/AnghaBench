#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct wmi_tim_info_arg {scalar_t__ tim_mcast; scalar_t__* tim_bitmap; scalar_t__ tim_changed; scalar_t__ tim_len; } ;
struct sk_buff {int* data; } ;
struct ieee80211_tim_ie {int bitmap_ctrl; scalar_t__ dtim_count; int /*<<< orphan*/  dtim_period; int /*<<< orphan*/  virtual_map; } ;
struct ieee80211_hdr {int /*<<< orphan*/  frame_control; } ;
struct TYPE_4__ {int* tim_bitmap; int tim_len; } ;
struct TYPE_5__ {TYPE_1__ ap; } ;
struct ath10k_vif {scalar_t__ vdev_type; TYPE_2__ u; } ;
struct ath10k {int dummy; } ;
typedef  scalar_t__ __le32 ;
struct TYPE_6__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_MGMT ; 
 TYPE_3__* ATH10K_SKB_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  ATH10K_SKB_F_DELIVER_CAB ; 
 int /*<<< orphan*/  ATH10K_SKB_F_DTIM_ZERO ; 
 int /*<<< orphan*/  WLAN_EID_TIM ; 
 scalar_t__ WMI_VDEV_TYPE_IBSS ; 
 int __le32_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*,scalar_t__,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*,...) ; 
 scalar_t__ cfg80211_find_ie (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  ieee80211_hdrlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  memmove (void*,void*,int) ; 
 scalar_t__ skb_put (struct sk_buff*,int) ; 
 int* skb_tail_pointer (struct sk_buff*) ; 

__attribute__((used)) static void ath10k_wmi_update_tim(struct ath10k *ar,
				  struct ath10k_vif *arvif,
				  struct sk_buff *bcn,
				  const struct wmi_tim_info_arg *tim_info)
{
	struct ieee80211_hdr *hdr = (struct ieee80211_hdr *)bcn->data;
	struct ieee80211_tim_ie *tim;
	u8 *ies, *ie;
	u8 ie_len, pvm_len;
	__le32 t;
	u32 v, tim_len;

	/* When FW reports 0 in tim_len, ensure atleast first byte
	 * in tim_bitmap is considered for pvm calculation.
	 */
	tim_len = tim_info->tim_len ? __le32_to_cpu(tim_info->tim_len) : 1;

	/* if next SWBA has no tim_changed the tim_bitmap is garbage.
	 * we must copy the bitmap upon change and reuse it later
	 */
	if (__le32_to_cpu(tim_info->tim_changed)) {
		int i;

		if (sizeof(arvif->u.ap.tim_bitmap) < tim_len) {
			ath10k_warn(ar, "SWBA TIM field is too big (%u), truncated it to %zu",
				    tim_len, sizeof(arvif->u.ap.tim_bitmap));
			tim_len = sizeof(arvif->u.ap.tim_bitmap);
		}

		for (i = 0; i < tim_len; i++) {
			t = tim_info->tim_bitmap[i / 4];
			v = __le32_to_cpu(t);
			arvif->u.ap.tim_bitmap[i] = (v >> ((i % 4) * 8)) & 0xFF;
		}

		/* FW reports either length 0 or length based on max supported
		 * station. so we calculate this on our own
		 */
		arvif->u.ap.tim_len = 0;
		for (i = 0; i < tim_len; i++)
			if (arvif->u.ap.tim_bitmap[i])
				arvif->u.ap.tim_len = i;

		arvif->u.ap.tim_len++;
	}

	ies = bcn->data;
	ies += ieee80211_hdrlen(hdr->frame_control);
	ies += 12; /* fixed parameters */

	ie = (u8 *)cfg80211_find_ie(WLAN_EID_TIM, ies,
				    (u8 *)skb_tail_pointer(bcn) - ies);
	if (!ie) {
		if (arvif->vdev_type != WMI_VDEV_TYPE_IBSS)
			ath10k_warn(ar, "no tim ie found;\n");
		return;
	}

	tim = (void *)ie + 2;
	ie_len = ie[1];
	pvm_len = ie_len - 3; /* exclude dtim count, dtim period, bmap ctl */

	if (pvm_len < arvif->u.ap.tim_len) {
		int expand_size = tim_len - pvm_len;
		int move_size = skb_tail_pointer(bcn) - (ie + 2 + ie_len);
		void *next_ie = ie + 2 + ie_len;

		if (skb_put(bcn, expand_size)) {
			memmove(next_ie + expand_size, next_ie, move_size);

			ie[1] += expand_size;
			ie_len += expand_size;
			pvm_len += expand_size;
		} else {
			ath10k_warn(ar, "tim expansion failed\n");
		}
	}

	if (pvm_len > tim_len) {
		ath10k_warn(ar, "tim pvm length is too great (%d)\n", pvm_len);
		return;
	}

	tim->bitmap_ctrl = !!__le32_to_cpu(tim_info->tim_mcast);
	memcpy(tim->virtual_map, arvif->u.ap.tim_bitmap, pvm_len);

	if (tim->dtim_count == 0) {
		ATH10K_SKB_CB(bcn)->flags |= ATH10K_SKB_F_DTIM_ZERO;

		if (__le32_to_cpu(tim_info->tim_mcast) == 1)
			ATH10K_SKB_CB(bcn)->flags |= ATH10K_SKB_F_DELIVER_CAB;
	}

	ath10k_dbg(ar, ATH10K_DBG_MGMT, "dtim %d/%d mcast %d pvmlen %d\n",
		   tim->dtim_count, tim->dtim_period,
		   tim->bitmap_ctrl, pvm_len);
}