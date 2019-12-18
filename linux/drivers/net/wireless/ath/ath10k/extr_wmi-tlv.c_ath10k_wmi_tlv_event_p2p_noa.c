#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct wmi_tlv_p2p_noa_ev {int /*<<< orphan*/  vdev_id; } ;
struct wmi_p2p_noa_info {int /*<<< orphan*/  num_descriptors; } ;
struct sk_buff {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct ath10k {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_WMI ; 
 int EPROTO ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ IS_ERR (void const**) ; 
 int PTR_ERR (void const**) ; 
 size_t WMI_TLV_TAG_STRUCT_P2P_NOA_EVENT ; 
 size_t WMI_TLV_TAG_STRUCT_P2P_NOA_INFO ; 
 int __le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath10k_p2p_noa_update_by_vdev_id (struct ath10k*,int,struct wmi_p2p_noa_info const*) ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*,int) ; 
 void** ath10k_wmi_tlv_parse_alloc (struct ath10k*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (void const**) ; 

__attribute__((used)) static int ath10k_wmi_tlv_event_p2p_noa(struct ath10k *ar,
					struct sk_buff *skb)
{
	const void **tb;
	const struct wmi_tlv_p2p_noa_ev *ev;
	const struct wmi_p2p_noa_info *noa;
	int ret, vdev_id;

	tb = ath10k_wmi_tlv_parse_alloc(ar, skb->data, skb->len, GFP_ATOMIC);
	if (IS_ERR(tb)) {
		ret = PTR_ERR(tb);
		ath10k_warn(ar, "failed to parse tlv: %d\n", ret);
		return ret;
	}

	ev = tb[WMI_TLV_TAG_STRUCT_P2P_NOA_EVENT];
	noa = tb[WMI_TLV_TAG_STRUCT_P2P_NOA_INFO];

	if (!ev || !noa) {
		kfree(tb);
		return -EPROTO;
	}

	vdev_id = __le32_to_cpu(ev->vdev_id);

	ath10k_dbg(ar, ATH10K_DBG_WMI,
		   "wmi tlv p2p noa vdev_id %i descriptors %hhu\n",
		   vdev_id, noa->num_descriptors);

	ath10k_p2p_noa_update_by_vdev_id(ar, vdev_id, noa);
	kfree(tb);
	return 0;
}