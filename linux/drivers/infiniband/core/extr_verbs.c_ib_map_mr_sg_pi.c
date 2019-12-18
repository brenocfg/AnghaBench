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
struct scatterlist {int dummy; } ;
struct ib_mr {scalar_t__ type; unsigned int page_size; TYPE_2__* device; } ;
struct TYPE_3__ {int (* map_mr_sg_pi ) (struct ib_mr*,struct scatterlist*,int,unsigned int*,struct scatterlist*,int,unsigned int*) ;} ;
struct TYPE_4__ {TYPE_1__ ops; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 scalar_t__ IB_MR_TYPE_INTEGRITY ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int stub1 (struct ib_mr*,struct scatterlist*,int,unsigned int*,struct scatterlist*,int,unsigned int*) ; 
 scalar_t__ unlikely (int) ; 

int ib_map_mr_sg_pi(struct ib_mr *mr, struct scatterlist *data_sg,
		    int data_sg_nents, unsigned int *data_sg_offset,
		    struct scatterlist *meta_sg, int meta_sg_nents,
		    unsigned int *meta_sg_offset, unsigned int page_size)
{
	if (unlikely(!mr->device->ops.map_mr_sg_pi ||
		     WARN_ON_ONCE(mr->type != IB_MR_TYPE_INTEGRITY)))
		return -EOPNOTSUPP;

	mr->page_size = page_size;

	return mr->device->ops.map_mr_sg_pi(mr, data_sg, data_sg_nents,
					    data_sg_offset, meta_sg,
					    meta_sg_nents, meta_sg_offset);
}