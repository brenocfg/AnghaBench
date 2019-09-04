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
 int /*<<< orphan*/  omap2xxx_cm_mpu_retention_allowed () ; 
 scalar_t__ sti_console_enabled ; 

__attribute__((used)) static int omap2_allow_mpu_retention(void)
{
	if (!omap2xxx_cm_mpu_retention_allowed())
		return 0;
	if (sti_console_enabled)
		return 0;

	return 1;
}