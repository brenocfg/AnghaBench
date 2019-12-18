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
struct ab8500_fg {TYPE_1__* fg_psy; int /*<<< orphan*/  parent; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ab8505_fg_sysfs_psy_attrs ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ is_ab8505 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ab8500_fg_sysfs_psy_remove_attrs(struct ab8500_fg *di)
{
	unsigned int i;

	if (is_ab8505(di->parent)) {
		for (i = 0; i < ARRAY_SIZE(ab8505_fg_sysfs_psy_attrs); i++)
			(void)device_remove_file(&di->fg_psy->dev,
						 &ab8505_fg_sysfs_psy_attrs[i]);
	}
}