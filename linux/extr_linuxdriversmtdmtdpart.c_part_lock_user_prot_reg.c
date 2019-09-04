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
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_2__ {int (* _lock_user_prot_reg ) (TYPE_1__*,int /*<<< orphan*/ ,size_t) ;} ;

/* Variables and functions */
 struct mtd_part* mtd_to_part (struct mtd_info*) ; 
 int stub1 (TYPE_1__*,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static int part_lock_user_prot_reg(struct mtd_info *mtd, loff_t from,
		size_t len)
{
	struct mtd_part *part = mtd_to_part(mtd);
	return part->parent->_lock_user_prot_reg(part->parent, from, len);
}