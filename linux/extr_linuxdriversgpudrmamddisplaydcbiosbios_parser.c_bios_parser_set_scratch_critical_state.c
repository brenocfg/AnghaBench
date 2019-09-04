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
struct dc_bios {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bios_set_scratch_critical_state (struct dc_bios*,int) ; 

__attribute__((used)) static void bios_parser_set_scratch_critical_state(
	struct dc_bios *dcb,
	bool state)
{
	bios_set_scratch_critical_state(dcb, state);
}