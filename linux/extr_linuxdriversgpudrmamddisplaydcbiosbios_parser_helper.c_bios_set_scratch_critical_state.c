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
 int /*<<< orphan*/  BIOS_SCRATCH_6 ; 
 int /*<<< orphan*/  REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  S6_CRITICAL_STATE ; 

void bios_set_scratch_critical_state(
	struct dc_bios *bios,
	bool state)
{
	uint32_t critial_state = state ? 1 : 0;
	REG_UPDATE(BIOS_SCRATCH_6, S6_CRITICAL_STATE, critial_state);
}