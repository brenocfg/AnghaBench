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
typedef  int /*<<< orphan*/  uint64_t ;
struct mtd_info {int /*<<< orphan*/  size; } ;
struct TYPE_2__ {struct mtd_info* parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  mtd_is_partition (struct mtd_info const*) ; 
 TYPE_1__* mtd_to_part (struct mtd_info const*) ; 

uint64_t mtd_get_device_size(const struct mtd_info *mtd)
{
	if (!mtd_is_partition(mtd))
		return mtd->size;

	return mtd_get_device_size(mtd_to_part(mtd)->parent);
}