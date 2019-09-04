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
typedef  int u64 ;
struct rbdr_entry_t {int buf_addr; } ;
struct TYPE_3__ {int q_len; } ;
struct rbdr {scalar_t__ enable; TYPE_1__ dmem; } ;
struct queue_set {int rbdr_cnt; int rbdr_len; struct rbdr* rbdr; } ;
struct nicvf {int rb_alloc_fail; TYPE_2__* pnicvf; struct queue_set* qs; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_4__ {int /*<<< orphan*/  netdev; } ;

/* Variables and functions */
 struct rbdr_entry_t* GET_RBDR_DESC (struct rbdr*,int) ; 
 int /*<<< orphan*/  NICVF_INTR_RBDR ; 
 int NICVF_RCV_BUF_ALIGN_BYTES ; 
 int /*<<< orphan*/  NIC_QSET_RBDR_0_1_DOOR ; 
 int /*<<< orphan*/  NIC_QSET_RBDR_0_1_STATUS0 ; 
 int /*<<< orphan*/  NIC_QSET_RBDR_0_1_TAIL ; 
 int /*<<< orphan*/  RCV_FRAG_LEN ; 
 scalar_t__ netif_running (int /*<<< orphan*/ ) ; 
 scalar_t__ nicvf_alloc_rcv_buffer (struct nicvf*,struct rbdr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  nicvf_enable_intr (struct nicvf*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nicvf_get_page (struct nicvf*) ; 
 int nicvf_queue_reg_read (struct nicvf*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nicvf_queue_reg_write (struct nicvf*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  smp_rmb () ; 
 int /*<<< orphan*/  smp_wmb () ; 

__attribute__((used)) static void nicvf_refill_rbdr(struct nicvf *nic, gfp_t gfp)
{
	struct queue_set *qs = nic->qs;
	int rbdr_idx = qs->rbdr_cnt;
	int tail, qcount;
	int refill_rb_cnt;
	struct rbdr *rbdr;
	struct rbdr_entry_t *desc;
	u64 rbuf;
	int new_rb = 0;

refill:
	if (!rbdr_idx)
		return;
	rbdr_idx--;
	rbdr = &qs->rbdr[rbdr_idx];
	/* Check if it's enabled */
	if (!rbdr->enable)
		goto next_rbdr;

	/* Get no of desc's to be refilled */
	qcount = nicvf_queue_reg_read(nic, NIC_QSET_RBDR_0_1_STATUS0, rbdr_idx);
	qcount &= 0x7FFFF;
	/* Doorbell can be ringed with a max of ring size minus 1 */
	if (qcount >= (qs->rbdr_len - 1))
		goto next_rbdr;
	else
		refill_rb_cnt = qs->rbdr_len - qcount - 1;

	/* Sync page cache info */
	smp_rmb();

	/* Start filling descs from tail */
	tail = nicvf_queue_reg_read(nic, NIC_QSET_RBDR_0_1_TAIL, rbdr_idx) >> 3;
	while (refill_rb_cnt) {
		tail++;
		tail &= (rbdr->dmem.q_len - 1);

		if (nicvf_alloc_rcv_buffer(nic, rbdr, gfp, RCV_FRAG_LEN, &rbuf))
			break;

		desc = GET_RBDR_DESC(rbdr, tail);
		desc->buf_addr = rbuf & ~(NICVF_RCV_BUF_ALIGN_BYTES - 1);
		refill_rb_cnt--;
		new_rb++;
	}

	nicvf_get_page(nic);

	/* make sure all memory stores are done before ringing doorbell */
	smp_wmb();

	/* Check if buffer allocation failed */
	if (refill_rb_cnt)
		nic->rb_alloc_fail = true;
	else
		nic->rb_alloc_fail = false;

	/* Notify HW */
	nicvf_queue_reg_write(nic, NIC_QSET_RBDR_0_1_DOOR,
			      rbdr_idx, new_rb);
next_rbdr:
	/* Re-enable RBDR interrupts only if buffer allocation is success */
	if (!nic->rb_alloc_fail && rbdr->enable &&
	    netif_running(nic->pnicvf->netdev))
		nicvf_enable_intr(nic, NICVF_INTR_RBDR, rbdr_idx);

	if (rbdr_idx)
		goto refill;
}