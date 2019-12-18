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
struct intel_th {int num_thdevs; int /*<<< orphan*/  id; int /*<<< orphan*/  major; int /*<<< orphan*/  dev; int /*<<< orphan*/ ** thdev; int /*<<< orphan*/ * hub; } ;

/* Variables and functions */
 int /*<<< orphan*/  TH_POSSIBLE_OUTPUTS ; 
 int /*<<< orphan*/  __unregister_chrdev (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_th_device_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_th_ida ; 
 int /*<<< orphan*/  intel_th_request_hub_module_flush (struct intel_th*) ; 
 int /*<<< orphan*/  kfree (struct intel_th*) ; 
 int /*<<< orphan*/  pm_runtime_forbid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 

void intel_th_free(struct intel_th *th)
{
	int i;

	intel_th_request_hub_module_flush(th);

	intel_th_device_remove(th->hub);
	for (i = 0; i < th->num_thdevs; i++) {
		if (th->thdev[i] != th->hub)
			intel_th_device_remove(th->thdev[i]);
		th->thdev[i] = NULL;
	}

	th->num_thdevs = 0;

	pm_runtime_get_sync(th->dev);
	pm_runtime_forbid(th->dev);

	__unregister_chrdev(th->major, 0, TH_POSSIBLE_OUTPUTS,
			    "intel_th/output");

	ida_simple_remove(&intel_th_ida, th->id);

	kfree(th);
}