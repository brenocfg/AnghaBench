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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct hsi_controller {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_for_each_child (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct hsi_controller* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ssi_debug_remove_ctrl (struct hsi_controller*) ; 
 int /*<<< orphan*/  ssi_remove_controller (struct hsi_controller*) ; 
 int /*<<< orphan*/  ssi_remove_ports ; 

__attribute__((used)) static int ssi_remove(struct platform_device *pd)
{
	struct hsi_controller *ssi = platform_get_drvdata(pd);

	/* cleanup of of_platform_populate() call */
	device_for_each_child(&pd->dev, NULL, ssi_remove_ports);

#ifdef CONFIG_DEBUG_FS
	ssi_debug_remove_ctrl(ssi);
#endif
	ssi_remove_controller(ssi);
	platform_set_drvdata(pd, NULL);

	pm_runtime_disable(&pd->dev);

	return 0;
}