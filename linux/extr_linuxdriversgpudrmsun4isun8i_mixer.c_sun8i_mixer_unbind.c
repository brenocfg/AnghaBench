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
struct sun8i_mixer {int /*<<< orphan*/  reset; int /*<<< orphan*/  bus_clk; int /*<<< orphan*/  mod_clk; TYPE_1__ engine; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct sun8i_mixer* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reset_control_assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sun8i_mixer_unbind(struct device *dev, struct device *master,
				 void *data)
{
	struct sun8i_mixer *mixer = dev_get_drvdata(dev);

	list_del(&mixer->engine.list);

	clk_disable_unprepare(mixer->mod_clk);
	clk_disable_unprepare(mixer->bus_clk);
	reset_control_assert(mixer->reset);
}