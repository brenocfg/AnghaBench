#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct rx_pkt_attrib {int qos; int /*<<< orphan*/  seq_num; int /*<<< orphan*/  amsdu; } ;
struct TYPE_3__ {struct recv_reorder_ctrl* preorder_ctrl; struct rx_pkt_attrib attrib; } ;
struct TYPE_4__ {TYPE_1__ hdr; } ;
union recv_frame {TYPE_2__ u; } ;
struct __queue {int /*<<< orphan*/  lock; } ;
struct recv_reorder_ctrl {int /*<<< orphan*/  reordering_ctrl_timer; struct __queue pending_recvframe_queue; } ;
struct _adapter {int /*<<< orphan*/  surprise_removed; int /*<<< orphan*/  driver_stopped; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  REORDER_WAIT_TIME ; 
 int /*<<< orphan*/  check_indicate_seq (struct recv_reorder_ctrl*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  enqueue_reorder_recvframe (struct recv_reorder_ctrl*,union recv_frame*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r8712_recv_indicatepkt (struct _adapter*,union recv_frame*) ; 
 scalar_t__ r8712_recv_indicatepkts_in_order (struct _adapter*,struct recv_reorder_ctrl*,int) ; 
 int /*<<< orphan*/  r8712_wlanhdr_to_ethhdr (union recv_frame*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int recv_indicatepkt_reorder(struct _adapter *padapter,
			     union recv_frame *prframe)
{
	unsigned long irql;
	struct rx_pkt_attrib *pattrib = &prframe->u.hdr.attrib;
	struct recv_reorder_ctrl *preorder_ctrl = prframe->u.hdr.preorder_ctrl;
	struct  __queue *ppending_recvframe_queue =
			 &preorder_ctrl->pending_recvframe_queue;

	if (!pattrib->amsdu) {
		/* s1. */
		r8712_wlanhdr_to_ethhdr(prframe);
		if (pattrib->qos != 1) {
			if (!padapter->driver_stopped &&
			    !padapter->surprise_removed) {
				r8712_recv_indicatepkt(padapter, prframe);
				return 0;
			} else {
				return -EINVAL;
			}
		}
	}
	spin_lock_irqsave(&ppending_recvframe_queue->lock, irql);
	/*s2. check if winstart_b(indicate_seq) needs to be updated*/
	if (!check_indicate_seq(preorder_ctrl, pattrib->seq_num))
		goto _err_exit;
	/*s3. Insert all packet into Reorder Queue to maintain its ordering.*/
	if (!enqueue_reorder_recvframe(preorder_ctrl, prframe))
		goto _err_exit;
	/*s4.
	 * Indication process.
	 * After Packet dropping and Sliding Window shifting as above, we can
	 * now just indicate the packets with the SeqNum smaller than latest
	 * WinStart and buffer other packets.
	 *
	 * For Rx Reorder condition:
	 * 1. All packets with SeqNum smaller than WinStart => Indicate
	 * 2. All packets with SeqNum larger than or equal to
	 * WinStart => Buffer it.
	 */
	if (r8712_recv_indicatepkts_in_order(padapter, preorder_ctrl, false)) {
		mod_timer(&preorder_ctrl->reordering_ctrl_timer,
			  jiffies + msecs_to_jiffies(REORDER_WAIT_TIME));
		spin_unlock_irqrestore(&ppending_recvframe_queue->lock, irql);
	} else {
		spin_unlock_irqrestore(&ppending_recvframe_queue->lock, irql);
		del_timer(&preorder_ctrl->reordering_ctrl_timer);
	}
	return 0;
_err_exit:
	spin_unlock_irqrestore(&ppending_recvframe_queue->lock, irql);
	return -ENOMEM;
}