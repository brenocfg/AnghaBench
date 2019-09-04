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
typedef  int /*<<< orphan*/  u_char ;
struct mtd_part {scalar_t__ offset; TYPE_1__* parent; } ;
struct mtd_info {int dummy; } ;
typedef  scalar_t__ loff_t ;
struct TYPE_2__ {int (* _write ) (TYPE_1__*,scalar_t__,size_t,size_t*,int /*<<< orphan*/  const*) ;} ;

/* Variables and functions */
 struct mtd_part* mtd_to_part (struct mtd_info*) ; 
 int stub1 (TYPE_1__*,scalar_t__,size_t,size_t*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int part_write(struct mtd_info *mtd, loff_t to, size_t len,
		size_t *retlen, const u_char *buf)
{
	struct mtd_part *part = mtd_to_part(mtd);
	return part->parent->_write(part->parent, to + part->offset, len,
				    retlen, buf);
}