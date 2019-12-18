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
typedef  int /*<<< orphan*/  u8 ;
struct controller_priv {int /*<<< orphan*/  ctrl_lock; scalar_t__ cpld_base; int /*<<< orphan*/  control_reg; } ;

/* Variables and functions */
 scalar_t__ CPLD_CONTROL ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 
 int /*<<< orphan*/  writeb (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void do_reset(struct controller_priv *cd, u8 rst_bit, bool reset)
{
	mutex_lock(&cd->ctrl_lock);
	/*
	 * CPLD_CONTROL is write-only, so cache its value in
	 * cd->control_reg
	 */
	if (reset)
		cd->control_reg &= ~rst_bit;
	else
		cd->control_reg |= rst_bit;
	writeb(cd->control_reg, cd->cpld_base + CPLD_CONTROL);
	/*
	 * h/w work-around:
	 * the hardware is 'too fast', so a reset followed by an immediate
	 * not-reset will _not_ change the anybus reset line in any way,
	 * losing the reset. to prevent this from happening, introduce
	 * a minimum reset duration.
	 * Verified minimum safe duration required using a scope
	 * on 14-June-2018: 100 us.
	 */
	if (reset)
		usleep_range(100, 200);
	mutex_unlock(&cd->ctrl_lock);
}