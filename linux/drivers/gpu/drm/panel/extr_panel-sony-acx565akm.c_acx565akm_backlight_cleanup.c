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
struct acx565akm_panel {TYPE_2__* backlight; scalar_t__ has_cabc; } ;
struct TYPE_3__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_4__ {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  acx565akm_cabc_attr_group ; 
 int /*<<< orphan*/  backlight_device_unregister (TYPE_2__*) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void acx565akm_backlight_cleanup(struct acx565akm_panel *lcd)
{
	if (lcd->has_cabc)
		sysfs_remove_group(&lcd->backlight->dev.kobj,
				   &acx565akm_cabc_attr_group);

	backlight_device_unregister(lcd->backlight);
}