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
struct qib_devdata {int dummy; } ;

/* Variables and functions */
 int BACTRL (int /*<<< orphan*/ ) ; 
 int EPB_GLOBAL_WR ; 
 int LDOUTCTRL1 (int /*<<< orphan*/ ) ; 
 int RXHSSTATUS (int /*<<< orphan*/ ) ; 
 int VCDL_CTRL2 (int /*<<< orphan*/ ) ; 
 int VCDL_DAC2 (int /*<<< orphan*/ ) ; 
 int ibsd_mod_allchnls (struct qib_devdata*,int,int,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int qib_sd_dactrim(struct qib_devdata *dd)
{
	int ret;

	ret = ibsd_mod_allchnls(dd, VCDL_DAC2(0) | EPB_GLOBAL_WR, 0x2D, 0xFF);
	if (ret < 0)
		goto bail;

	/* more fine-tuning of what will be default */
	ret = ibsd_mod_allchnls(dd, VCDL_CTRL2(0), 3, 0xF);
	if (ret < 0)
		goto bail;

	ret = ibsd_mod_allchnls(dd, BACTRL(0) | EPB_GLOBAL_WR, 0x40, 0xFF);
	if (ret < 0)
		goto bail;

	ret = ibsd_mod_allchnls(dd, LDOUTCTRL1(0) | EPB_GLOBAL_WR, 0x04, 0xFF);
	if (ret < 0)
		goto bail;

	ret = ibsd_mod_allchnls(dd, RXHSSTATUS(0) | EPB_GLOBAL_WR, 0x04, 0xFF);
	if (ret < 0)
		goto bail;

	/*
	 * Delay for max possible number of steps, with slop.
	 * Each step is about 4usec.
	 */
	udelay(415);

	ret = ibsd_mod_allchnls(dd, LDOUTCTRL1(0) | EPB_GLOBAL_WR, 0x00, 0xFF);

bail:
	return ret;
}