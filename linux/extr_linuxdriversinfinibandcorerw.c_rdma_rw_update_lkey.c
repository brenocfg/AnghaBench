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
struct TYPE_5__ {int /*<<< orphan*/  lkey; } ;
struct TYPE_4__ {int /*<<< orphan*/  key; } ;
struct rdma_rw_reg_ctx {TYPE_3__* mr; TYPE_2__ sge; TYPE_1__ reg_wr; } ;
struct TYPE_6__ {int need_inval; int /*<<< orphan*/  lkey; } ;

/* Variables and functions */
 int /*<<< orphan*/  ib_inc_rkey (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_update_fast_reg_key (TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rdma_rw_update_lkey(struct rdma_rw_reg_ctx *reg, bool need_inval)
{
	reg->mr->need_inval = need_inval;
	ib_update_fast_reg_key(reg->mr, ib_inc_rkey(reg->mr->lkey));
	reg->reg_wr.key = reg->mr->lkey;
	reg->sge.lkey = reg->mr->lkey;
}