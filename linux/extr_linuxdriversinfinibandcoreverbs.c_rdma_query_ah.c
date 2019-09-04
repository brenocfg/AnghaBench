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
struct TYPE_3__ {int /*<<< orphan*/ * sgid_attr; } ;
struct rdma_ah_attr {TYPE_1__ grh; } ;
struct ib_ah {TYPE_2__* device; } ;
struct TYPE_4__ {int (* query_ah ) (struct ib_ah*,struct rdma_ah_attr*) ;} ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int stub1 (struct ib_ah*,struct rdma_ah_attr*) ; 

int rdma_query_ah(struct ib_ah *ah, struct rdma_ah_attr *ah_attr)
{
	ah_attr->grh.sgid_attr = NULL;

	return ah->device->query_ah ?
		ah->device->query_ah(ah, ah_attr) :
		-EOPNOTSUPP;
}