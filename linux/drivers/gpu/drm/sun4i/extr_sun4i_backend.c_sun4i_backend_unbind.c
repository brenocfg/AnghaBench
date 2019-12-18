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
struct TYPE_2__ {int /*<<< orphan*/  list; } ;
struct sun4i_backend {int /*<<< orphan*/  reset; int /*<<< orphan*/  bus_clk; int /*<<< orphan*/  mod_clk; int /*<<< orphan*/  ram_clk; TYPE_1__ engine; } ;
struct device {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct sun4i_backend* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 scalar_t__ of_device_is_compatible (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  reset_control_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sun4i_backend_free_sat (struct device*) ; 

__attribute__((used)) static void sun4i_backend_unbind(struct device *dev, struct device *master,
				 void *data)
{
	struct sun4i_backend *backend = dev_get_drvdata(dev);

	list_del(&backend->engine.list);

	if (of_device_is_compatible(dev->of_node,
				    "allwinner,sun8i-a33-display-backend"))
		sun4i_backend_free_sat(dev);

	clk_disable_unprepare(backend->ram_clk);
	clk_disable_unprepare(backend->mod_clk);
	clk_disable_unprepare(backend->bus_clk);
	reset_control_assert(backend->reset);
}