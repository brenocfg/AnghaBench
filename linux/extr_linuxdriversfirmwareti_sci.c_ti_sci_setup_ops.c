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
struct ti_sci_clk_ops {int /*<<< orphan*/  get_freq; int /*<<< orphan*/  set_freq; int /*<<< orphan*/  get_best_match_freq; int /*<<< orphan*/  get_num_parents; int /*<<< orphan*/  get_parent; int /*<<< orphan*/  set_parent; int /*<<< orphan*/  is_off; int /*<<< orphan*/  is_on; int /*<<< orphan*/  is_auto; int /*<<< orphan*/  put_clock; int /*<<< orphan*/  idle_clock; int /*<<< orphan*/  get_clock; } ;
struct ti_sci_dev_ops {int /*<<< orphan*/  get_device_resets; int /*<<< orphan*/  set_device_resets; int /*<<< orphan*/  is_transitioning; int /*<<< orphan*/  is_on; int /*<<< orphan*/  is_stop; int /*<<< orphan*/  is_idle; int /*<<< orphan*/  get_context_loss_count; int /*<<< orphan*/  is_valid; int /*<<< orphan*/  put_device; int /*<<< orphan*/  idle_device; int /*<<< orphan*/  get_device; } ;
struct ti_sci_core_ops {int /*<<< orphan*/  reboot_device; } ;
struct ti_sci_ops {struct ti_sci_clk_ops clk_ops; struct ti_sci_dev_ops dev_ops; struct ti_sci_core_ops core_ops; } ;
struct TYPE_2__ {struct ti_sci_ops ops; } ;
struct ti_sci_info {TYPE_1__ handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  ti_sci_cmd_clk_get_freq ; 
 int /*<<< orphan*/  ti_sci_cmd_clk_get_match_freq ; 
 int /*<<< orphan*/  ti_sci_cmd_clk_get_num_parents ; 
 int /*<<< orphan*/  ti_sci_cmd_clk_get_parent ; 
 int /*<<< orphan*/  ti_sci_cmd_clk_is_auto ; 
 int /*<<< orphan*/  ti_sci_cmd_clk_is_off ; 
 int /*<<< orphan*/  ti_sci_cmd_clk_is_on ; 
 int /*<<< orphan*/  ti_sci_cmd_clk_set_freq ; 
 int /*<<< orphan*/  ti_sci_cmd_clk_set_parent ; 
 int /*<<< orphan*/  ti_sci_cmd_core_reboot ; 
 int /*<<< orphan*/  ti_sci_cmd_dev_get_clcnt ; 
 int /*<<< orphan*/  ti_sci_cmd_dev_is_idle ; 
 int /*<<< orphan*/  ti_sci_cmd_dev_is_on ; 
 int /*<<< orphan*/  ti_sci_cmd_dev_is_stop ; 
 int /*<<< orphan*/  ti_sci_cmd_dev_is_trans ; 
 int /*<<< orphan*/  ti_sci_cmd_dev_is_valid ; 
 int /*<<< orphan*/  ti_sci_cmd_get_clock ; 
 int /*<<< orphan*/  ti_sci_cmd_get_device ; 
 int /*<<< orphan*/  ti_sci_cmd_get_device_resets ; 
 int /*<<< orphan*/  ti_sci_cmd_idle_clock ; 
 int /*<<< orphan*/  ti_sci_cmd_idle_device ; 
 int /*<<< orphan*/  ti_sci_cmd_put_clock ; 
 int /*<<< orphan*/  ti_sci_cmd_put_device ; 
 int /*<<< orphan*/  ti_sci_cmd_set_device_resets ; 

__attribute__((used)) static void ti_sci_setup_ops(struct ti_sci_info *info)
{
	struct ti_sci_ops *ops = &info->handle.ops;
	struct ti_sci_core_ops *core_ops = &ops->core_ops;
	struct ti_sci_dev_ops *dops = &ops->dev_ops;
	struct ti_sci_clk_ops *cops = &ops->clk_ops;

	core_ops->reboot_device = ti_sci_cmd_core_reboot;

	dops->get_device = ti_sci_cmd_get_device;
	dops->idle_device = ti_sci_cmd_idle_device;
	dops->put_device = ti_sci_cmd_put_device;

	dops->is_valid = ti_sci_cmd_dev_is_valid;
	dops->get_context_loss_count = ti_sci_cmd_dev_get_clcnt;
	dops->is_idle = ti_sci_cmd_dev_is_idle;
	dops->is_stop = ti_sci_cmd_dev_is_stop;
	dops->is_on = ti_sci_cmd_dev_is_on;
	dops->is_transitioning = ti_sci_cmd_dev_is_trans;
	dops->set_device_resets = ti_sci_cmd_set_device_resets;
	dops->get_device_resets = ti_sci_cmd_get_device_resets;

	cops->get_clock = ti_sci_cmd_get_clock;
	cops->idle_clock = ti_sci_cmd_idle_clock;
	cops->put_clock = ti_sci_cmd_put_clock;
	cops->is_auto = ti_sci_cmd_clk_is_auto;
	cops->is_on = ti_sci_cmd_clk_is_on;
	cops->is_off = ti_sci_cmd_clk_is_off;

	cops->set_parent = ti_sci_cmd_clk_set_parent;
	cops->get_parent = ti_sci_cmd_clk_get_parent;
	cops->get_num_parents = ti_sci_cmd_clk_get_num_parents;

	cops->get_best_match_freq = ti_sci_cmd_clk_get_match_freq;
	cops->set_freq = ti_sci_cmd_clk_set_freq;
	cops->get_freq = ti_sci_cmd_clk_get_freq;
}