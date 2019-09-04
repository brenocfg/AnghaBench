#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int quirks; int syss_mask; } ;
struct sysc {int* offsets; TYPE_3__ cfg; scalar_t__ module_va; TYPE_2__* cap; int /*<<< orphan*/  dev; scalar_t__ legacy_mode; } ;
struct TYPE_5__ {TYPE_1__* regbits; } ;
struct TYPE_4__ {int srst_shift; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MAX_MODULE_SOFTRESET_WAIT ; 
 int SYSC_QUIRK_NO_RESET_ON_INIT ; 
 size_t SYSC_SYSCONFIG ; 
 size_t SYSC_SYSSTATUS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int readl_poll_timeout (scalar_t__,int,int,int,int /*<<< orphan*/ ) ; 
 int sysc_read (struct sysc*,int) ; 
 int /*<<< orphan*/  sysc_write (struct sysc*,int,int) ; 

__attribute__((used)) static int sysc_reset(struct sysc *ddata)
{
	int offset = ddata->offsets[SYSC_SYSCONFIG];
	int val;

	if (ddata->legacy_mode || offset < 0 ||
	    ddata->cfg.quirks & SYSC_QUIRK_NO_RESET_ON_INIT)
		return 0;

	/*
	 * Currently only support reset status in sysstatus.
	 * Warn and return error in all other cases
	 */
	if (!ddata->cfg.syss_mask) {
		dev_err(ddata->dev, "No ti,syss-mask. Reset failed\n");
		return -EINVAL;
	}

	val = sysc_read(ddata, offset);
	val |= (0x1 << ddata->cap->regbits->srst_shift);
	sysc_write(ddata, offset, val);

	/* Poll on reset status */
	offset = ddata->offsets[SYSC_SYSSTATUS];

	return readl_poll_timeout(ddata->module_va + offset, val,
				  (val & ddata->cfg.syss_mask) == 0x0,
				  100, MAX_MODULE_SOFTRESET_WAIT);
}