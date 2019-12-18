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
struct platform_device {int dummy; } ;
struct controller_priv {int /*<<< orphan*/  reset_gpiod; TYPE_1__* class_dev; } ;
struct TYPE_2__ {int id; } ;

/* Variables and functions */
 int /*<<< orphan*/  controller_index_ida ; 
 int /*<<< orphan*/  device_unregister (TYPE_1__*) ; 
 int /*<<< orphan*/  gpiod_set_value_cansleep (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int) ; 
 struct controller_priv* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int controller_remove(struct platform_device *pdev)
{
	struct controller_priv *cd = platform_get_drvdata(pdev);
	int id = cd->class_dev->id;

	device_unregister(cd->class_dev);
	ida_simple_remove(&controller_index_ida, id);
	gpiod_set_value_cansleep(cd->reset_gpiod, 1);
	return 0;
}