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
struct kvec {int dummy; } ;
typedef  scalar_t__ loff_t ;
struct TYPE_2__ {int (* _writev ) (TYPE_1__*,struct kvec const*,unsigned long,scalar_t__,size_t*) ;} ;

/* Variables and functions */
 struct mtd_part* mtd_to_part (struct mtd_info*) ; 
 int stub1 (TYPE_1__*,struct kvec const*,unsigned long,scalar_t__,size_t*) ; 

__attribute__((used)) static int part_writev(struct mtd_info *mtd, const struct kvec *vecs,
		unsigned long count, loff_t to, size_t *retlen)
{
	struct mtd_part *part = mtd_to_part(mtd);
	return part->parent->_writev(part->parent, vecs, count,
				     to + part->offset, retlen);
}