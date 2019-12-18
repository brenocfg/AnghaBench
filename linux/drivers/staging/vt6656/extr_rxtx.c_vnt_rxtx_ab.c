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
union vnt_tx_data_head {int /*<<< orphan*/  data_head_ab; int /*<<< orphan*/  data_head_a_fb; int /*<<< orphan*/  rts_ab; int /*<<< orphan*/  rts_a_fb; } ;
struct TYPE_4__ {union vnt_tx_data_head head; } ;
struct TYPE_5__ {TYPE_1__ mic; union vnt_tx_data_head head; } ;
struct vnt_rrv_time_ab {void* rts_rrv_time; int /*<<< orphan*/  rrv_time; } ;
struct TYPE_6__ {TYPE_2__ tx; struct vnt_rrv_time_ab ab; } ;
union vnt_tx_head {TYPE_3__ tx_ab; } ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct vnt_usb_send_context {int /*<<< orphan*/  pkt_type; scalar_t__ fb_option; int /*<<< orphan*/  need_ack; int /*<<< orphan*/  tx_rate; int /*<<< orphan*/  frame_len; struct vnt_private* priv; } ;
struct vnt_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PK_TYPE_11A ; 
 int /*<<< orphan*/  PK_TYPE_11B ; 
 void* vnt_get_rtscts_rsvtime_le (struct vnt_private*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnt_rxtx_datahead_a_fb (struct vnt_usb_send_context*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vnt_rxtx_datahead_ab (struct vnt_usb_send_context*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vnt_rxtx_rsvtime_le16 (struct vnt_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnt_rxtx_rts_a_fb_head (struct vnt_usb_send_context*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vnt_rxtx_rts_ab_head (struct vnt_usb_send_context*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static u16 vnt_rxtx_ab(struct vnt_usb_send_context *tx_context,
		       union vnt_tx_head *tx_head, bool need_rts, bool need_mic)
{
	struct vnt_private *priv = tx_context->priv;
	struct vnt_rrv_time_ab *buf = &tx_head->tx_ab.ab;
	union vnt_tx_data_head *head = &tx_head->tx_ab.tx.head;
	u32 frame_len = tx_context->frame_len;
	u16 current_rate = tx_context->tx_rate;
	u8 need_ack = tx_context->need_ack;

	buf->rrv_time = vnt_rxtx_rsvtime_le16(priv, tx_context->pkt_type,
					      frame_len, current_rate, need_ack);

	if (need_mic)
		head = &tx_head->tx_ab.tx.mic.head;

	if (need_rts) {
		if (tx_context->pkt_type == PK_TYPE_11B)
			buf->rts_rrv_time = vnt_get_rtscts_rsvtime_le(priv, 0,
				tx_context->pkt_type, frame_len, current_rate);
		else /* PK_TYPE_11A */
			buf->rts_rrv_time = vnt_get_rtscts_rsvtime_le(priv, 2,
				tx_context->pkt_type, frame_len, current_rate);

		if (tx_context->fb_option &&
		    tx_context->pkt_type == PK_TYPE_11A)
			return vnt_rxtx_rts_a_fb_head(tx_context,
						      &head->rts_a_fb);

		return vnt_rxtx_rts_ab_head(tx_context, &head->rts_ab);
	}

	if (tx_context->pkt_type == PK_TYPE_11A)
		return vnt_rxtx_datahead_a_fb(tx_context,
					      &head->data_head_a_fb);

	return vnt_rxtx_datahead_ab(tx_context, &head->data_head_ab);
}