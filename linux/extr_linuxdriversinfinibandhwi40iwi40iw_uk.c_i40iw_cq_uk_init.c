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
struct i40iw_cqe {int dummy; } ;
struct i40iw_cq_uk_init_info {scalar_t__ cq_size; int /*<<< orphan*/  avoid_mem_cflct; int /*<<< orphan*/  shadow_area; int /*<<< orphan*/  cqe_alloc_reg; int /*<<< orphan*/  cq_id; scalar_t__ cq_base; } ;
struct i40iw_cq_uk {scalar_t__ cq_size; int polarity; int /*<<< orphan*/  ops; int /*<<< orphan*/  cq_ring; int /*<<< orphan*/  avoid_mem_cflct; int /*<<< orphan*/  shadow_area; int /*<<< orphan*/  cqe_alloc_reg; int /*<<< orphan*/  cq_id; struct i40iw_cqe* cq_base; } ;
typedef  enum i40iw_status_code { ____Placeholder_i40iw_status_code } i40iw_status_code ;

/* Variables and functions */
 int I40IW_ERR_INVALID_SIZE ; 
 scalar_t__ I40IW_MAX_CQ_SIZE ; 
 scalar_t__ I40IW_MIN_CQ_SIZE ; 
 int /*<<< orphan*/  I40IW_RING_INIT (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  iw_cq_ops ; 

enum i40iw_status_code i40iw_cq_uk_init(struct i40iw_cq_uk *cq,
					struct i40iw_cq_uk_init_info *info)
{
	if ((info->cq_size < I40IW_MIN_CQ_SIZE) ||
	    (info->cq_size > I40IW_MAX_CQ_SIZE))
		return I40IW_ERR_INVALID_SIZE;
	cq->cq_base = (struct i40iw_cqe *)info->cq_base;
	cq->cq_id = info->cq_id;
	cq->cq_size = info->cq_size;
	cq->cqe_alloc_reg = info->cqe_alloc_reg;
	cq->shadow_area = info->shadow_area;
	cq->avoid_mem_cflct = info->avoid_mem_cflct;

	I40IW_RING_INIT(cq->cq_ring, cq->cq_size);
	cq->polarity = 1;
	cq->ops = iw_cq_ops;

	return 0;
}