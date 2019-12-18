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
typedef  scalar_t__ u16 ;
struct sk_buff {scalar_t__ cb; scalar_t__ data; } ;
struct rtllib_hdr_3addr {void* seq_ctl; int /*<<< orphan*/  frame_ctl; } ;
struct rtllib_device {short softmac_features; int* seq_ctrl; int /*<<< orphan*/  dev; int /*<<< orphan*/  (* softmac_hard_start_xmit ) (struct sk_buff*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  basic_rate; int /*<<< orphan*/  (* softmac_data_hard_start_xmit ) (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;scalar_t__ disable_mgnt_queue; } ;
struct cb_desc {int RATRIndex; int bTxDisableRateFallBack; int bTxUseDriverAssingedRate; int /*<<< orphan*/  data_rate; void* queue_index; } ;

/* Variables and functions */
 void* HIGH_QUEUE ; 
 short IEEE_SOFTMAC_SINGLE_QUEUE ; 
 void* MGNT_QUEUE ; 
 int /*<<< orphan*/  MgntQuery_MgntFrameTxRate (struct rtllib_device*) ; 
 scalar_t__ RTLLIB_FTYPE_CTL ; 
 scalar_t__ RTLLIB_STYPE_PSPOLL ; 
 scalar_t__ WLAN_FC_GET_STYPE (scalar_t__) ; 
 scalar_t__ WLAN_FC_GET_TYPE (scalar_t__) ; 
 void* cpu_to_le16 (int) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
softmac_ps_mgmt_xmit(struct sk_buff *skb,
		     struct rtllib_device *ieee)
{
	short single = ieee->softmac_features & IEEE_SOFTMAC_SINGLE_QUEUE;
	struct rtllib_hdr_3addr  *header =
		(struct rtllib_hdr_3addr  *) skb->data;
	u16 fc, type, stype;
	struct cb_desc *tcb_desc = (struct cb_desc *)(skb->cb + 8);

	fc = le16_to_cpu(header->frame_ctl);
	type = WLAN_FC_GET_TYPE(fc);
	stype = WLAN_FC_GET_STYPE(fc);


	if (stype != RTLLIB_STYPE_PSPOLL)
		tcb_desc->queue_index = MGNT_QUEUE;
	else
		tcb_desc->queue_index = HIGH_QUEUE;

	if (ieee->disable_mgnt_queue)
		tcb_desc->queue_index = HIGH_QUEUE;


	tcb_desc->data_rate = MgntQuery_MgntFrameTxRate(ieee);
	tcb_desc->RATRIndex = 7;
	tcb_desc->bTxDisableRateFallBack = 1;
	tcb_desc->bTxUseDriverAssingedRate = 1;
	if (single) {
		if (type != RTLLIB_FTYPE_CTL) {
			header->seq_ctl = cpu_to_le16(ieee->seq_ctrl[0] << 4);

			if (ieee->seq_ctrl[0] == 0xFFF)
				ieee->seq_ctrl[0] = 0;
			else
				ieee->seq_ctrl[0]++;

		}
		/* avoid watchdog triggers */
		ieee->softmac_data_hard_start_xmit(skb, ieee->dev,
						   ieee->basic_rate);

	} else {
		if (type != RTLLIB_FTYPE_CTL) {
			header->seq_ctl = cpu_to_le16(ieee->seq_ctrl[0] << 4);

			if (ieee->seq_ctrl[0] == 0xFFF)
				ieee->seq_ctrl[0] = 0;
			else
				ieee->seq_ctrl[0]++;
		}
		ieee->softmac_hard_start_xmit(skb, ieee->dev);

	}
}