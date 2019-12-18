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
struct sk_buff {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  qp_type; } ;
struct rdma_counter_mode {scalar_t__ mode; int mask; TYPE_1__ param; } ;
struct rdma_counter {struct rdma_counter_mode mode; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 int RDMA_COUNTER_MASK_QP_TYPE ; 
 scalar_t__ RDMA_COUNTER_MODE_AUTO ; 
 int /*<<< orphan*/  RDMA_NLDEV_ATTR_RES_TYPE ; 
 int /*<<< orphan*/  RDMA_NLDEV_ATTR_STAT_MODE ; 
 scalar_t__ nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ nla_put_u8 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fill_stat_counter_mode(struct sk_buff *msg,
				  struct rdma_counter *counter)
{
	struct rdma_counter_mode *m = &counter->mode;

	if (nla_put_u32(msg, RDMA_NLDEV_ATTR_STAT_MODE, m->mode))
		return -EMSGSIZE;

	if (m->mode == RDMA_COUNTER_MODE_AUTO)
		if ((m->mask & RDMA_COUNTER_MASK_QP_TYPE) &&
		    nla_put_u8(msg, RDMA_NLDEV_ATTR_RES_TYPE, m->param.qp_type))
			return -EMSGSIZE;

	return 0;
}