#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  invalidate_rkey; } ;
struct TYPE_7__ {int /*<<< orphan*/ * next; TYPE_2__ ex; int /*<<< orphan*/  opcode; } ;
struct TYPE_5__ {int /*<<< orphan*/  wr; } ;
struct rdma_rw_reg_ctx {TYPE_3__ inv_wr; TYPE_1__ reg_wr; TYPE_4__* mr; } ;
struct TYPE_8__ {int /*<<< orphan*/  lkey; scalar_t__ need_inval; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_WR_LOCAL_INV ; 

__attribute__((used)) static inline int rdma_rw_inv_key(struct rdma_rw_reg_ctx *reg)
{
	int count = 0;

	if (reg->mr->need_inval) {
		reg->inv_wr.opcode = IB_WR_LOCAL_INV;
		reg->inv_wr.ex.invalidate_rkey = reg->mr->lkey;
		reg->inv_wr.next = &reg->reg_wr.wr;
		count++;
	} else {
		reg->inv_wr.next = NULL;
	}

	return count;
}