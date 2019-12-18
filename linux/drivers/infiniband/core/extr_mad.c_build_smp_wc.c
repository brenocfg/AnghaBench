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
typedef  void* u16 ;
struct ib_wc {int byte_len; int /*<<< orphan*/  port_num; scalar_t__ dlid_path_bits; scalar_t__ sl; void* slid; struct ib_qp* qp; int /*<<< orphan*/  src_qp; void* pkey_index; int /*<<< orphan*/  opcode; int /*<<< orphan*/  status; struct ib_cqe* wr_cqe; } ;
struct ib_qp {int dummy; } ;
struct ib_mad {int dummy; } ;
struct ib_grh {int dummy; } ;
struct ib_cqe {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_QP0 ; 
 int /*<<< orphan*/  IB_WC_RECV ; 
 int /*<<< orphan*/  IB_WC_SUCCESS ; 
 int /*<<< orphan*/  memset (struct ib_wc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void build_smp_wc(struct ib_qp *qp, struct ib_cqe *cqe, u16 slid,
		u16 pkey_index, u8 port_num, struct ib_wc *wc)
{
	memset(wc, 0, sizeof *wc);
	wc->wr_cqe = cqe;
	wc->status = IB_WC_SUCCESS;
	wc->opcode = IB_WC_RECV;
	wc->pkey_index = pkey_index;
	wc->byte_len = sizeof(struct ib_mad) + sizeof(struct ib_grh);
	wc->src_qp = IB_QP0;
	wc->qp = qp;
	wc->slid = slid;
	wc->sl = 0;
	wc->dlid_path_bits = 0;
	wc->port_num = port_num;
}