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
struct sysc {int /*<<< orphan*/  rsts; TYPE_1__ cfg; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int SYSC_QUIRK_NO_RESET_ON_INIT ; 
 int /*<<< orphan*/  devm_reset_control_array_get_optional_exclusive (int /*<<< orphan*/ ) ; 
 int reset_control_assert (int /*<<< orphan*/ ) ; 
 int reset_control_deassert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sysc_init_resets(struct sysc *ddata)
{
	int error;

	ddata->rsts =
		devm_reset_control_array_get_optional_exclusive(ddata->dev);
	if (IS_ERR(ddata->rsts))
		return PTR_ERR(ddata->rsts);

	if (ddata->cfg.quirks & SYSC_QUIRK_NO_RESET_ON_INIT)
		goto deassert;

	error = reset_control_assert(ddata->rsts);
	if (error)
		return error;

deassert:
	error = reset_control_deassert(ddata->rsts);
	if (error)
		return error;

	return 0;
}