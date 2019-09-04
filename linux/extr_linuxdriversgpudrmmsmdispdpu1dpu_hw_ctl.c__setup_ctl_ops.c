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
struct dpu_hw_ctl_ops {int /*<<< orphan*/  get_bitmask_cdm; int /*<<< orphan*/  get_bitmask_intf; int /*<<< orphan*/  get_bitmask_mixer; int /*<<< orphan*/  get_bitmask_sspp; int /*<<< orphan*/  setup_blendstage; int /*<<< orphan*/  clear_all_blendstages; int /*<<< orphan*/  wait_reset_status; int /*<<< orphan*/  reset; int /*<<< orphan*/  setup_intf_cfg; int /*<<< orphan*/  trigger_pending; int /*<<< orphan*/  trigger_start; int /*<<< orphan*/  get_flush_register; int /*<<< orphan*/  trigger_flush; int /*<<< orphan*/  get_pending_flush; int /*<<< orphan*/  update_pending_flush; int /*<<< orphan*/  clear_pending_flush; } ;

/* Variables and functions */
 int /*<<< orphan*/  dpu_hw_ctl_clear_all_blendstages ; 
 int /*<<< orphan*/  dpu_hw_ctl_clear_pending_flush ; 
 int /*<<< orphan*/  dpu_hw_ctl_get_bitmask_cdm ; 
 int /*<<< orphan*/  dpu_hw_ctl_get_bitmask_intf ; 
 int /*<<< orphan*/  dpu_hw_ctl_get_bitmask_mixer ; 
 int /*<<< orphan*/  dpu_hw_ctl_get_bitmask_sspp ; 
 int /*<<< orphan*/  dpu_hw_ctl_get_flush_register ; 
 int /*<<< orphan*/  dpu_hw_ctl_get_pending_flush ; 
 int /*<<< orphan*/  dpu_hw_ctl_intf_cfg ; 
 int /*<<< orphan*/  dpu_hw_ctl_reset_control ; 
 int /*<<< orphan*/  dpu_hw_ctl_setup_blendstage ; 
 int /*<<< orphan*/  dpu_hw_ctl_trigger_flush ; 
 int /*<<< orphan*/  dpu_hw_ctl_trigger_pending ; 
 int /*<<< orphan*/  dpu_hw_ctl_trigger_start ; 
 int /*<<< orphan*/  dpu_hw_ctl_update_pending_flush ; 
 int /*<<< orphan*/  dpu_hw_ctl_wait_reset_status ; 

__attribute__((used)) static void _setup_ctl_ops(struct dpu_hw_ctl_ops *ops,
		unsigned long cap)
{
	ops->clear_pending_flush = dpu_hw_ctl_clear_pending_flush;
	ops->update_pending_flush = dpu_hw_ctl_update_pending_flush;
	ops->get_pending_flush = dpu_hw_ctl_get_pending_flush;
	ops->trigger_flush = dpu_hw_ctl_trigger_flush;
	ops->get_flush_register = dpu_hw_ctl_get_flush_register;
	ops->trigger_start = dpu_hw_ctl_trigger_start;
	ops->trigger_pending = dpu_hw_ctl_trigger_pending;
	ops->setup_intf_cfg = dpu_hw_ctl_intf_cfg;
	ops->reset = dpu_hw_ctl_reset_control;
	ops->wait_reset_status = dpu_hw_ctl_wait_reset_status;
	ops->clear_all_blendstages = dpu_hw_ctl_clear_all_blendstages;
	ops->setup_blendstage = dpu_hw_ctl_setup_blendstage;
	ops->get_bitmask_sspp = dpu_hw_ctl_get_bitmask_sspp;
	ops->get_bitmask_mixer = dpu_hw_ctl_get_bitmask_mixer;
	ops->get_bitmask_intf = dpu_hw_ctl_get_bitmask_intf;
	ops->get_bitmask_cdm = dpu_hw_ctl_get_bitmask_cdm;
}