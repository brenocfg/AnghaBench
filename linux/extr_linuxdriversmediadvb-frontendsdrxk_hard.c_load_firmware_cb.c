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
struct firmware {int dummy; } ;
struct drxk_state {struct firmware const* fw; int /*<<< orphan*/ * microcode_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  dprintk (int,char*,char*) ; 
 int /*<<< orphan*/  init_drxk (struct drxk_state*) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void load_firmware_cb(const struct firmware *fw,
			     void *context)
{
	struct drxk_state *state = context;

	dprintk(1, ": %s\n", fw ? "firmware loaded" : "firmware not loaded");
	if (!fw) {
		pr_err("Could not load firmware file %s.\n",
			state->microcode_name);
		pr_info("Copy %s to your hotplug directory!\n",
			state->microcode_name);
		state->microcode_name = NULL;

		/*
		 * As firmware is now load asynchronous, it is not possible
		 * anymore to fail at frontend attach. We might silently
		 * return here, and hope that the driver won't crash.
		 * We might also change all DVB callbacks to return -ENODEV
		 * if the device is not initialized.
		 * As the DRX-K devices have their own internal firmware,
		 * let's just hope that it will match a firmware revision
		 * compatible with this driver and proceed.
		 */
	}
	state->fw = fw;

	init_drxk(state);
}