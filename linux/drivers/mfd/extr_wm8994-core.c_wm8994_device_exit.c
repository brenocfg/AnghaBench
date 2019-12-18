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
struct wm8994 {int /*<<< orphan*/  dev; int /*<<< orphan*/  supplies; int /*<<< orphan*/  num_supplies; } ;

/* Variables and functions */
 int /*<<< orphan*/  mfd_remove_devices (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regulator_bulk_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regulator_bulk_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wm8994_irq_exit (struct wm8994*) ; 

__attribute__((used)) static void wm8994_device_exit(struct wm8994 *wm8994)
{
	pm_runtime_disable(wm8994->dev);
	wm8994_irq_exit(wm8994);
	regulator_bulk_disable(wm8994->num_supplies, wm8994->supplies);
	regulator_bulk_free(wm8994->num_supplies, wm8994->supplies);
	mfd_remove_devices(wm8994->dev);
}