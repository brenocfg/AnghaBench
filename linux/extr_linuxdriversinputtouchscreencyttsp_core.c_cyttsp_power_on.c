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
struct TYPE_2__ {int /*<<< orphan*/  bl_status; int /*<<< orphan*/  bl_file; } ;
struct cyttsp {int /*<<< orphan*/  state; TYPE_1__ bl_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  CY_ACTIVE_STATE ; 
 scalar_t__ CY_OPERATE_MODE ; 
 int ENODEV ; 
 scalar_t__ GET_BOOTLOADERMODE (int /*<<< orphan*/ ) ; 
 scalar_t__ GET_HSTMODE (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_OPERATIONAL_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_VALID_APP (int /*<<< orphan*/ ) ; 
 int cyttsp_act_dist_setup (struct cyttsp*) ; 
 int cyttsp_exit_bl_mode (struct cyttsp*) ; 
 int cyttsp_load_bl_regs (struct cyttsp*) ; 
 int cyttsp_set_operational_mode (struct cyttsp*) ; 
 int cyttsp_set_sysinfo_mode (struct cyttsp*) ; 
 int cyttsp_set_sysinfo_regs (struct cyttsp*) ; 
 int cyttsp_soft_reset (struct cyttsp*) ; 

__attribute__((used)) static int cyttsp_power_on(struct cyttsp *ts)
{
	int error;

	error = cyttsp_soft_reset(ts);
	if (error)
		return error;

	error = cyttsp_load_bl_regs(ts);
	if (error)
		return error;

	if (GET_BOOTLOADERMODE(ts->bl_data.bl_status) &&
	    IS_VALID_APP(ts->bl_data.bl_status)) {
		error = cyttsp_exit_bl_mode(ts);
		if (error)
			return error;
	}

	if (GET_HSTMODE(ts->bl_data.bl_file) != CY_OPERATE_MODE ||
	    IS_OPERATIONAL_ERR(ts->bl_data.bl_status)) {
		return -ENODEV;
	}

	error = cyttsp_set_sysinfo_mode(ts);
	if (error)
		return error;

	error = cyttsp_set_sysinfo_regs(ts);
	if (error)
		return error;

	error = cyttsp_set_operational_mode(ts);
	if (error)
		return error;

	/* init active distance */
	error = cyttsp_act_dist_setup(ts);
	if (error)
		return error;

	ts->state = CY_ACTIVE_STATE;

	return 0;
}