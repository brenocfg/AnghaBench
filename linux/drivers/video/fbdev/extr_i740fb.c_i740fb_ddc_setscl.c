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
struct i740fb_par {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DDC_SCL ; 
 int /*<<< orphan*/  REG_DDC_DRIVE ; 
 int /*<<< orphan*/  REG_DDC_STATE ; 
 int /*<<< orphan*/  XRX ; 
 int /*<<< orphan*/  i740outreg_mask (struct i740fb_par*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void i740fb_ddc_setscl(void *data, int val)
{
	struct i740fb_par *par = data;

	i740outreg_mask(par, XRX, REG_DDC_DRIVE, DDC_SCL, DDC_SCL);
	i740outreg_mask(par, XRX, REG_DDC_STATE, val ? DDC_SCL : 0, DDC_SCL);
}