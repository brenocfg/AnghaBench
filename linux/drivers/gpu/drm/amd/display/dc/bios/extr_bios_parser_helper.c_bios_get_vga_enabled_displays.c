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
typedef  int uint32_t ;
struct dc_bios {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIOS_SCRATCH_3 ; 
 int REG_READ (int /*<<< orphan*/ ) ; 

uint32_t bios_get_vga_enabled_displays(
	struct dc_bios *bios)
{
	uint32_t active_disp = 1;

	active_disp = REG_READ(BIOS_SCRATCH_3) & 0XFFFF;
	return active_disp;
}