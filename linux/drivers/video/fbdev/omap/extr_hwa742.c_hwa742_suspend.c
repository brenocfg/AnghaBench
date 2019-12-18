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
struct TYPE_2__ {int /*<<< orphan*/  sys_ck; int /*<<< orphan*/  update_mode; int /*<<< orphan*/  update_mode_before_suspend; } ;

/* Variables and functions */
 int /*<<< orphan*/  HWA742_POWER_SAVE ; 
 int /*<<< orphan*/  OMAPFB_UPDATE_DISABLED ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 TYPE_1__ hwa742 ; 
 int /*<<< orphan*/  hwa742_set_update_mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hwa742_write_reg (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void hwa742_suspend(void)
{
	hwa742.update_mode_before_suspend = hwa742.update_mode;
	hwa742_set_update_mode(OMAPFB_UPDATE_DISABLED);
	/* Enable sleep mode */
	hwa742_write_reg(HWA742_POWER_SAVE, 1 << 1);
	clk_disable(hwa742.sys_ck);
}