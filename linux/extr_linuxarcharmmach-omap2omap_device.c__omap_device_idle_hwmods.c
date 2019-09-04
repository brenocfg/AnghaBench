#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct omap_device {int hwmods_cnt; int /*<<< orphan*/ * hwmods; } ;

/* Variables and functions */
 int omap_hwmod_idle (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int _omap_device_idle_hwmods(struct omap_device *od)
{
	int ret = 0;
	int i;

	for (i = 0; i < od->hwmods_cnt; i++)
		ret |= omap_hwmod_idle(od->hwmods[i]);

	return ret;
}