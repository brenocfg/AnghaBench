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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct vnt_usb_send_context {int /*<<< orphan*/  tx_hdr_size; int /*<<< orphan*/  pkt_type; int /*<<< orphan*/  need_ack; int /*<<< orphan*/  tx_rate; int /*<<< orphan*/  frame_len; struct vnt_private* priv; } ;
struct vnt_tx_datahead_g_fb {void* duration_a; int /*<<< orphan*/  hdr; void* time_stamp_off_b; void* time_stamp_off_a; void* duration_a_f1; void* duration_a_f0; void* duration_b; int /*<<< orphan*/  b; int /*<<< orphan*/  a; } ;
struct vnt_private {int /*<<< orphan*/  top_cck_basic_rate; } ;

/* Variables and functions */
 int /*<<< orphan*/  PK_TYPE_11B ; 
 int /*<<< orphan*/  le16_to_cpu (void*) ; 
 void* vnt_get_duration_le (struct vnt_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnt_get_phy_field (struct vnt_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vnt_mac_hdr_pos (struct vnt_usb_send_context*,int /*<<< orphan*/ *) ; 
 void* vnt_time_stamp_off (struct vnt_private*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u16 vnt_rxtx_datahead_g_fb(struct vnt_usb_send_context *tx_context,
				  struct vnt_tx_datahead_g_fb *buf)
{
	struct vnt_private *priv = tx_context->priv;
	u32 frame_len = tx_context->frame_len;
	u16 rate = tx_context->tx_rate;
	u8 need_ack = tx_context->need_ack;

	/* Get SignalField,ServiceField,Length */
	vnt_get_phy_field(priv, frame_len, rate, tx_context->pkt_type, &buf->a);

	vnt_get_phy_field(priv, frame_len, priv->top_cck_basic_rate,
			  PK_TYPE_11B, &buf->b);

	/* Get Duration and TimeStamp */
	buf->duration_a = vnt_get_duration_le(priv, tx_context->pkt_type,
					      need_ack);
	buf->duration_b = vnt_get_duration_le(priv, PK_TYPE_11B, need_ack);

	buf->duration_a_f0 = vnt_get_duration_le(priv, tx_context->pkt_type,
						 need_ack);
	buf->duration_a_f1 = vnt_get_duration_le(priv, tx_context->pkt_type,
						 need_ack);

	buf->time_stamp_off_a = vnt_time_stamp_off(priv, rate);
	buf->time_stamp_off_b = vnt_time_stamp_off(priv,
						   priv->top_cck_basic_rate);

	tx_context->tx_hdr_size = vnt_mac_hdr_pos(tx_context, &buf->hdr);

	return le16_to_cpu(buf->duration_a);
}