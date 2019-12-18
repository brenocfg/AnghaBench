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
struct ib_mr {unsigned int page_size; TYPE_2__* device; } ;
struct TYPE_3__ {int (* map_mr_sg ) (struct ib_mr*,struct scatterlist*,int,unsigned int*) ;} ;
struct TYPE_4__ {TYPE_1__ ops; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int stub1 (struct ib_mr*,struct scatterlist*,int,unsigned int*) ; 
 scalar_t__ unlikely (int) ; 

int ib_map_mr_sg(struct ib_mr *mr, struct scatterlist *sg, int sg_nents,
		 unsigned int *sg_offset, unsigned int page_size)
{
	if (unlikely(!mr->device->ops.map_mr_sg))
		return -EOPNOTSUPP;

	mr->page_size = page_size;

	return mr->device->ops.map_mr_sg(mr, sg, sg_nents, sg_offset);
}