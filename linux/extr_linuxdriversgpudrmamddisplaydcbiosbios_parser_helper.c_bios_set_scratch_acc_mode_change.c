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
 int /*<<< orphan*/  BIOS_SCRATCH_6 ; 
 int /*<<< orphan*/  REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  S6_ACC_MODE ; 

void bios_set_scratch_acc_mode_change(
	struct dc_bios *bios)
{
	REG_UPDATE(BIOS_SCRATCH_6, S6_ACC_MODE, 1);
}