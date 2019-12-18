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
typedef  int u8 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct wmi_data_hdr {int /*<<< orphan*/  info2; } ;
struct wmi_create_pstream_cmd {int traffic_class; int user_pri; int /*<<< orphan*/  tsid; int /*<<< orphan*/  inactivity_int; } ;
struct wmi {scalar_t__ traffic_class; int fat_pipe_exist; int /*<<< orphan*/  lock; } ;
struct sk_buff {int* data; scalar_t__ protocol; } ;
struct ethhdr {int dummy; } ;
struct ath6kl_llc_snap_hdr {scalar_t__ eth_type; } ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ETH_P_PAE ; 
 int /*<<< orphan*/  IP_ETHERTYPE ; 
 scalar_t__ WARN_ON (int /*<<< orphan*/ ) ; 
 int WMI_DATA_HDR_META_MASK ; 
 int WMI_DATA_HDR_META_SHIFT ; 
 int /*<<< orphan*/  WMI_IMPLICIT_PSTREAM ; 
 int /*<<< orphan*/  WMI_IMPLICIT_PSTREAM_INACTIVITY_INT ; 
 int WMI_MAX_TX_META_SZ ; 
 int WMI_VOICE_USER_PRIORITY ; 
 int WMM_AC_BE ; 
 scalar_t__ WMM_AC_VI ; 
 int /*<<< orphan*/  ath6kl_wmi_create_pstream_cmd (struct wmi*,int,struct wmi_create_pstream_cmd*) ; 
 int ath6kl_wmi_determine_user_priority (int*,int) ; 
 scalar_t__ cpu_to_be16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct wmi_create_pstream_cmd*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int* up_to_ac ; 
 int /*<<< orphan*/  wmi_data_hdr_set_up (struct wmi_data_hdr*,int) ; 

int ath6kl_wmi_implicit_create_pstream(struct wmi *wmi, u8 if_idx,
				       struct sk_buff *skb,
				       u32 layer2_priority, bool wmm_enabled,
				       u8 *ac)
{
	struct wmi_data_hdr *data_hdr;
	struct ath6kl_llc_snap_hdr *llc_hdr;
	struct wmi_create_pstream_cmd cmd;
	u32 meta_size, hdr_size;
	u16 ip_type = IP_ETHERTYPE;
	u8 stream_exist, usr_pri;
	u8 traffic_class = WMM_AC_BE;
	u8 *datap;

	if (WARN_ON(skb == NULL))
		return -EINVAL;

	datap = skb->data;
	data_hdr = (struct wmi_data_hdr *) datap;

	meta_size = ((le16_to_cpu(data_hdr->info2) >> WMI_DATA_HDR_META_SHIFT) &
		     WMI_DATA_HDR_META_MASK) ? WMI_MAX_TX_META_SZ : 0;

	if (!wmm_enabled) {
		/* If WMM is disabled all traffic goes as BE traffic */
		usr_pri = 0;
	} else {
		hdr_size = sizeof(struct ethhdr);

		llc_hdr = (struct ath6kl_llc_snap_hdr *)(datap +
							 sizeof(struct
								wmi_data_hdr) +
							 meta_size + hdr_size);

		if (llc_hdr->eth_type == htons(ip_type)) {
			/*
			 * Extract the endpoint info from the TOS field
			 * in the IP header.
			 */
			usr_pri =
			   ath6kl_wmi_determine_user_priority(((u8 *) llc_hdr) +
					sizeof(struct ath6kl_llc_snap_hdr),
					layer2_priority);
		} else {
			usr_pri = layer2_priority & 0x7;
		}

		/*
		 * Queue the EAPOL frames in the same WMM_AC_VO queue
		 * as that of management frames.
		 */
		if (skb->protocol == cpu_to_be16(ETH_P_PAE))
			usr_pri = WMI_VOICE_USER_PRIORITY;
	}

	/*
	 * workaround for WMM S5
	 *
	 * FIXME: wmi->traffic_class is always 100 so this test doesn't
	 * make sense
	 */
	if ((wmi->traffic_class == WMM_AC_VI) &&
	    ((usr_pri == 5) || (usr_pri == 4)))
		usr_pri = 1;

	/* Convert user priority to traffic class */
	traffic_class = up_to_ac[usr_pri & 0x7];

	wmi_data_hdr_set_up(data_hdr, usr_pri);

	spin_lock_bh(&wmi->lock);
	stream_exist = wmi->fat_pipe_exist;
	spin_unlock_bh(&wmi->lock);

	if (!(stream_exist & (1 << traffic_class))) {
		memset(&cmd, 0, sizeof(cmd));
		cmd.traffic_class = traffic_class;
		cmd.user_pri = usr_pri;
		cmd.inactivity_int =
			cpu_to_le32(WMI_IMPLICIT_PSTREAM_INACTIVITY_INT);
		/* Implicit streams are created with TSID 0xFF */
		cmd.tsid = WMI_IMPLICIT_PSTREAM;
		ath6kl_wmi_create_pstream_cmd(wmi, if_idx, &cmd);
	}

	*ac = traffic_class;

	return 0;
}