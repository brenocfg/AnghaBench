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
struct mtd_part {TYPE_1__* parent; } ;
struct mtd_info {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* _sync ) (TYPE_1__*) ;} ;

/* Variables and functions */
 struct mtd_part* mtd_to_part (struct mtd_info*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 

__attribute__((used)) static void part_sync(struct mtd_info *mtd)
{
	struct mtd_part *part = mtd_to_part(mtd);
	part->parent->_sync(part->parent);
}