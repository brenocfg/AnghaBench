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
typedef  int u8 ;
struct mipi_dbi {int dummy; } ;

/* Variables and functions */
 int DCS_POWER_MODE_DISPLAY ; 
 int DCS_POWER_MODE_DISPLAY_NORMAL_MODE ; 
 int DCS_POWER_MODE_RESERVED_MASK ; 
 int DCS_POWER_MODE_SLEEP_MODE ; 
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*) ; 
 int /*<<< orphan*/  MIPI_DCS_GET_POWER_MODE ; 
 scalar_t__ mipi_dbi_command_read (struct mipi_dbi*,int /*<<< orphan*/ ,int*) ; 

bool mipi_dbi_display_is_on(struct mipi_dbi *dbi)
{
	u8 val;

	if (mipi_dbi_command_read(dbi, MIPI_DCS_GET_POWER_MODE, &val))
		return false;

	val &= ~DCS_POWER_MODE_RESERVED_MASK;

	/* The poweron/reset value is 08h DCS_POWER_MODE_DISPLAY_NORMAL_MODE */
	if (val != (DCS_POWER_MODE_DISPLAY |
	    DCS_POWER_MODE_DISPLAY_NORMAL_MODE | DCS_POWER_MODE_SLEEP_MODE))
		return false;

	DRM_DEBUG_DRIVER("Display is ON\n");

	return true;
}