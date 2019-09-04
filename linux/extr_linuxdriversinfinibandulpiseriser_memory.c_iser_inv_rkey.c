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
struct TYPE_2__ {int /*<<< orphan*/  invalidate_rkey; } ;
struct ib_send_wr {scalar_t__ num_sge; scalar_t__ send_flags; TYPE_1__ ex; struct ib_cqe* wr_cqe; int /*<<< orphan*/  opcode; } ;
struct ib_mr {int /*<<< orphan*/  rkey; } ;
struct ib_cqe {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_WR_LOCAL_INV ; 

__attribute__((used)) static inline void
iser_inv_rkey(struct ib_send_wr *inv_wr,
	      struct ib_mr *mr,
	      struct ib_cqe *cqe)
{
	inv_wr->opcode = IB_WR_LOCAL_INV;
	inv_wr->wr_cqe = cqe;
	inv_wr->ex.invalidate_rkey = mr->rkey;
	inv_wr->send_flags = 0;
	inv_wr->num_sge = 0;
}