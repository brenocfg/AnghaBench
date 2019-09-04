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
struct TYPE_2__ {int quirks; } ;
struct sysc {int /*<<< orphan*/  dev; void* revision; TYPE_1__ cfg; } ;

/* Variables and functions */
 int SYSC_QUIRK_NO_IDLE_ON_INIT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysc_init_revision_quirks (struct sysc*) ; 
 void* sysc_read_revision (struct sysc*) ; 
 int sysc_reset (struct sysc*) ; 

__attribute__((used)) static int sysc_init_module(struct sysc *ddata)
{
	int error;

	if (ddata->cfg.quirks & SYSC_QUIRK_NO_IDLE_ON_INIT) {
		ddata->revision = sysc_read_revision(ddata);
		goto rev_quirks;
	}

	error = pm_runtime_get_sync(ddata->dev);
	if (error < 0) {
		pm_runtime_put_noidle(ddata->dev);

		return 0;
	}

	error = sysc_reset(ddata);
	if (error) {
		dev_err(ddata->dev, "Reset failed with %d\n", error);
		pm_runtime_put_sync(ddata->dev);

		return error;
	}

	ddata->revision = sysc_read_revision(ddata);
	pm_runtime_put_sync(ddata->dev);

rev_quirks:
	sysc_init_revision_quirks(ddata);

	return 0;
}