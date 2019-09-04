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
typedef  int /*<<< orphan*/  u8 ;
typedef  size_t u16 ;
struct qed_ll2_tx_packet {size_t bd_used; TYPE_1__* bds_set; } ;
struct TYPE_4__ {size_t cur_send_frag_num; int /*<<< orphan*/  lock; struct qed_ll2_tx_packet* cur_send_packet; } ;
struct qed_ll2_info {TYPE_2__ tx_queue; } ;
struct qed_hwfn {int dummy; } ;
struct core_tx_bd {int /*<<< orphan*/  nbytes; int /*<<< orphan*/  addr; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_3__ {size_t frag_len; int /*<<< orphan*/  tx_frag; struct core_tx_bd* txq_bd; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_REGPAIR_LE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int /*<<< orphan*/  cpu_to_le16 (size_t) ; 
 struct qed_ll2_info* qed_ll2_handle_sanity (struct qed_hwfn*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qed_ll2_tx_packet_notify (struct qed_hwfn*,struct qed_ll2_info*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int qed_ll2_set_fragment_of_tx_packet(void *cxt,
				      u8 connection_handle,
				      dma_addr_t addr, u16 nbytes)
{
	struct qed_ll2_tx_packet *p_cur_send_packet = NULL;
	struct qed_hwfn *p_hwfn = cxt;
	struct qed_ll2_info *p_ll2_conn = NULL;
	u16 cur_send_frag_num = 0;
	struct core_tx_bd *p_bd;
	unsigned long flags;

	p_ll2_conn = qed_ll2_handle_sanity(p_hwfn, connection_handle);
	if (!p_ll2_conn)
		return -EINVAL;

	if (!p_ll2_conn->tx_queue.cur_send_packet)
		return -EINVAL;

	p_cur_send_packet = p_ll2_conn->tx_queue.cur_send_packet;
	cur_send_frag_num = p_ll2_conn->tx_queue.cur_send_frag_num;

	if (cur_send_frag_num >= p_cur_send_packet->bd_used)
		return -EINVAL;

	/* Fill the BD information, and possibly notify FW */
	p_bd = p_cur_send_packet->bds_set[cur_send_frag_num].txq_bd;
	DMA_REGPAIR_LE(p_bd->addr, addr);
	p_bd->nbytes = cpu_to_le16(nbytes);
	p_cur_send_packet->bds_set[cur_send_frag_num].tx_frag = addr;
	p_cur_send_packet->bds_set[cur_send_frag_num].frag_len = nbytes;

	p_ll2_conn->tx_queue.cur_send_frag_num++;

	spin_lock_irqsave(&p_ll2_conn->tx_queue.lock, flags);
	qed_ll2_tx_packet_notify(p_hwfn, p_ll2_conn);
	spin_unlock_irqrestore(&p_ll2_conn->tx_queue.lock, flags);

	return 0;
}