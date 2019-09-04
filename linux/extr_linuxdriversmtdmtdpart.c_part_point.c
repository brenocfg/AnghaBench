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
struct mtd_part {scalar_t__ offset; TYPE_1__* parent; } ;
struct mtd_info {int dummy; } ;
typedef  int /*<<< orphan*/  resource_size_t ;
typedef  scalar_t__ loff_t ;
struct TYPE_2__ {int (* _point ) (TYPE_1__*,scalar_t__,size_t,size_t*,void**,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 struct mtd_part* mtd_to_part (struct mtd_info*) ; 
 int stub1 (TYPE_1__*,scalar_t__,size_t,size_t*,void**,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int part_point(struct mtd_info *mtd, loff_t from, size_t len,
		size_t *retlen, void **virt, resource_size_t *phys)
{
	struct mtd_part *part = mtd_to_part(mtd);

	return part->parent->_point(part->parent, from + part->offset, len,
				    retlen, virt, phys);
}