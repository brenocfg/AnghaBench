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
struct TYPE_2__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  fmc; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_unregister (int /*<<< orphan*/ *) ; 
 TYPE_1__* ff_current_dev ; 
 int /*<<< orphan*/  ff_nr_dev ; 
 int /*<<< orphan*/  ff_work ; 
 int /*<<< orphan*/  fmc_device_unregister_n (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ff_exit(void)
{
	if (ff_current_dev) {
		fmc_device_unregister_n(ff_current_dev->fmc, ff_nr_dev);
		device_unregister(&ff_current_dev->dev);
	}
	cancel_delayed_work_sync(&ff_work);
}