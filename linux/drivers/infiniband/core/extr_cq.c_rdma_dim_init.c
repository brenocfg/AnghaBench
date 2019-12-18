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
struct ib_cq {scalar_t__ poll_ctx; struct dim* dim; TYPE_2__* device; } ;
struct dim {int /*<<< orphan*/  work; struct ib_cq* priv; int /*<<< orphan*/  profile_ix; int /*<<< orphan*/  tune_state; int /*<<< orphan*/  state; } ;
struct TYPE_3__ {int /*<<< orphan*/  modify_cq; } ;
struct TYPE_4__ {int /*<<< orphan*/  use_cq_dim; TYPE_1__ ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIM_GOING_RIGHT ; 
 int /*<<< orphan*/  DIM_START_MEASURE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IB_POLL_DIRECT ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RDMA_DIM_START_PROFILE ; 
 int /*<<< orphan*/  ib_cq_rdma_dim_work ; 
 struct dim* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rdma_dim_init(struct ib_cq *cq)
{
	struct dim *dim;

	if (!cq->device->ops.modify_cq || !cq->device->use_cq_dim ||
	    cq->poll_ctx == IB_POLL_DIRECT)
		return;

	dim = kzalloc(sizeof(struct dim), GFP_KERNEL);
	if (!dim)
		return;

	dim->state = DIM_START_MEASURE;
	dim->tune_state = DIM_GOING_RIGHT;
	dim->profile_ix = RDMA_DIM_START_PROFILE;
	dim->priv = cq;
	cq->dim = dim;

	INIT_WORK(&dim->work, ib_cq_rdma_dim_work);
}