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
struct TYPE_2__ {int /*<<< orphan*/  has_accelerometer; } ;

/* Variables and functions */
 int /*<<< orphan*/  accelerometer_group ; 
 int /*<<< orphan*/  applesmc_destroy_nodes (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  applesmc_idev ; 
 int /*<<< orphan*/  input_free_polled_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_unregister_polled_device (int /*<<< orphan*/ ) ; 
 TYPE_1__ smcreg ; 

__attribute__((used)) static void applesmc_release_accelerometer(void)
{
	if (!smcreg.has_accelerometer)
		return;
	input_unregister_polled_device(applesmc_idev);
	input_free_polled_device(applesmc_idev);
	applesmc_destroy_nodes(accelerometer_group);
}