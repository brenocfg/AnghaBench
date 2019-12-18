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
struct platform_device {int dummy; } ;
struct ocelot {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ocelot_deinit (struct ocelot*) ; 
 int /*<<< orphan*/  ocelot_netdevice_nb ; 
 int /*<<< orphan*/  ocelot_switchdev_blocking_nb ; 
 int /*<<< orphan*/  ocelot_switchdev_nb ; 
 struct ocelot* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  unregister_netdevice_notifier (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_switchdev_blocking_notifier (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_switchdev_notifier (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mscc_ocelot_remove(struct platform_device *pdev)
{
	struct ocelot *ocelot = platform_get_drvdata(pdev);

	ocelot_deinit(ocelot);
	unregister_switchdev_blocking_notifier(&ocelot_switchdev_blocking_nb);
	unregister_switchdev_notifier(&ocelot_switchdev_nb);
	unregister_netdevice_notifier(&ocelot_netdevice_nb);

	return 0;
}