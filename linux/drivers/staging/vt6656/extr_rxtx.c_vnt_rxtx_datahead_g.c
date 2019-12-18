#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct vnt_usb_send_context {int /*<<< orphan*/  tx_hdr_size; int /*<<< orphan*/  pkt_type; int /*<<< orphan*/  need_ack; int /*<<< orphan*/  tx_rate; int /*<<< orphan*/  frame_len; TYPE_1__* skb; struct vnt_private* priv; } ;
struct vnt_tx_datahead_g {void* duration_a; int /*<<< orphan*/  hdr; void* time_stamp_off_b; void* time_stamp_off_a; void* duration_b; int /*<<< orphan*/  b; int /*<<< orphan*/  a; } ;
struct vnt_private {int current_aid; int /*<<< orphan*/  top_cck_basic_rate; } ;
struct ieee80211_hdr {int /*<<< orphan*/  frame_control; } ;
typedef  void* __le16 ;
struct TYPE_2__ {scalar_t__ data; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  PK_TYPE_11B ; 
 void* cpu_to_le16 (int) ; 
 scalar_t__ ieee80211_is_pspoll (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_to_cpu (void*) ; 
 void* vnt_get_duration_le (struct vnt_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnt_get_phy_field (struct vnt_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vnt_mac_hdr_pos (struct vnt_usb_send_context*,int /*<<< orphan*/ *) ; 
 void* vnt_time_stamp_off (struct vnt_private*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u16 vnt_rxtx_datahead_g(struct vnt_usb_send_context *tx_context,
			       struct vnt_tx_datahead_g *buf)
{
	struct vnt_private *priv = tx_context->priv;
	struct ieee80211_hdr *hdr =
				(struct ieee80211_hdr *)tx_context->skb->data;
	u32 frame_len = tx_context->frame_len;
	u16 rate = tx_context->tx_rate;
	u8 need_ack = tx_context->need_ack;

	/* Get SignalField,ServiceField,Length */
	vnt_get_phy_field(priv, frame_len, rate, tx_context->pkt_type, &buf->a);
	vnt_get_phy_field(priv, frame_len, priv->top_cck_basic_rate,
			  PK_TYPE_11B, &buf->b);

	/* Get Duration and TimeStamp */
	if (ieee80211_is_pspoll(hdr->frame_control)) {
		__le16 dur = cpu_to_le16(priv->current_aid | BIT(14) | BIT(15));

		buf->duration_a = dur;
		buf->duration_b = dur;
	} else {
		buf->duration_a = vnt_get_duration_le(priv,
						tx_context->pkt_type, need_ack);
		buf->duration_b = vnt_get_duration_le(priv,
						      PK_TYPE_11B, need_ack);
	}

	buf->time_stamp_off_a = vnt_time_stamp_off(priv, rate);
	buf->time_stamp_off_b = vnt_time_stamp_off(priv,
						   priv->top_cck_basic_rate);

	tx_context->tx_hdr_size = vnt_mac_hdr_pos(tx_context, &buf->hdr);

	return le16_to_cpu(buf->duration_a);
}