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
struct qib_devdata {TYPE_1__* cspec; } ;
struct TYPE_2__ {scalar_t__ presets_needed; } ;

/* Variables and functions */
 int /*<<< orphan*/  qib_ibsd_reset (struct qib_devdata*,int) ; 
 int qib_internal_presets (struct qib_devdata*) ; 
 int /*<<< orphan*/  qib_sd_trimdone_monitor (struct qib_devdata*,char*) ; 
 int /*<<< orphan*/  udelay (int) ; 

int qib_sd7220_presets(struct qib_devdata *dd)
{
	int ret = 0;

	if (!dd->cspec->presets_needed)
		return ret;
	dd->cspec->presets_needed = 0;
	/* Assert uC reset, so we don't clash with it. */
	qib_ibsd_reset(dd, 1);
	udelay(2);
	qib_sd_trimdone_monitor(dd, "link-down");

	ret = qib_internal_presets(dd);
	return ret;
}