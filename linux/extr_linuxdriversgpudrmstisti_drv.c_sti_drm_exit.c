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

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drivers ; 
 int /*<<< orphan*/  platform_unregister_drivers (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sti_drm_exit(void)
{
	platform_unregister_drivers(drivers, ARRAY_SIZE(drivers));
}