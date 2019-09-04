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
struct dpu_encoder_phys_ops {int /*<<< orphan*/  get_line_count; int /*<<< orphan*/  handle_post_kickoff; int /*<<< orphan*/  prepare_idle_pc; int /*<<< orphan*/  restore; int /*<<< orphan*/  irq_control; int /*<<< orphan*/  hw_reset; int /*<<< orphan*/  needs_single_flush; int /*<<< orphan*/  trigger_start; int /*<<< orphan*/  wait_for_vblank; int /*<<< orphan*/  wait_for_tx_complete; int /*<<< orphan*/  prepare_for_kickoff; int /*<<< orphan*/  wait_for_commit_done; int /*<<< orphan*/  control_vblank_irq; int /*<<< orphan*/  get_hw_resources; int /*<<< orphan*/  destroy; int /*<<< orphan*/  disable; int /*<<< orphan*/  enable; int /*<<< orphan*/  mode_fixup; int /*<<< orphan*/  mode_set; int /*<<< orphan*/  is_master; } ;

/* Variables and functions */
 int /*<<< orphan*/  dpu_encoder_helper_hw_reset ; 
 int /*<<< orphan*/  dpu_encoder_phys_cmd_control_vblank_irq ; 
 int /*<<< orphan*/  dpu_encoder_phys_cmd_destroy ; 
 int /*<<< orphan*/  dpu_encoder_phys_cmd_disable ; 
 int /*<<< orphan*/  dpu_encoder_phys_cmd_enable ; 
 int /*<<< orphan*/  dpu_encoder_phys_cmd_enable_helper ; 
 int /*<<< orphan*/  dpu_encoder_phys_cmd_get_hw_resources ; 
 int /*<<< orphan*/  dpu_encoder_phys_cmd_get_line_count ; 
 int /*<<< orphan*/  dpu_encoder_phys_cmd_handle_post_kickoff ; 
 int /*<<< orphan*/  dpu_encoder_phys_cmd_irq_control ; 
 int /*<<< orphan*/  dpu_encoder_phys_cmd_is_master ; 
 int /*<<< orphan*/  dpu_encoder_phys_cmd_mode_fixup ; 
 int /*<<< orphan*/  dpu_encoder_phys_cmd_mode_set ; 
 int /*<<< orphan*/  dpu_encoder_phys_cmd_needs_single_flush ; 
 int /*<<< orphan*/  dpu_encoder_phys_cmd_prepare_for_kickoff ; 
 int /*<<< orphan*/  dpu_encoder_phys_cmd_prepare_idle_pc ; 
 int /*<<< orphan*/  dpu_encoder_phys_cmd_trigger_start ; 
 int /*<<< orphan*/  dpu_encoder_phys_cmd_wait_for_commit_done ; 
 int /*<<< orphan*/  dpu_encoder_phys_cmd_wait_for_tx_complete ; 
 int /*<<< orphan*/  dpu_encoder_phys_cmd_wait_for_vblank ; 

__attribute__((used)) static void dpu_encoder_phys_cmd_init_ops(
		struct dpu_encoder_phys_ops *ops)
{
	ops->is_master = dpu_encoder_phys_cmd_is_master;
	ops->mode_set = dpu_encoder_phys_cmd_mode_set;
	ops->mode_fixup = dpu_encoder_phys_cmd_mode_fixup;
	ops->enable = dpu_encoder_phys_cmd_enable;
	ops->disable = dpu_encoder_phys_cmd_disable;
	ops->destroy = dpu_encoder_phys_cmd_destroy;
	ops->get_hw_resources = dpu_encoder_phys_cmd_get_hw_resources;
	ops->control_vblank_irq = dpu_encoder_phys_cmd_control_vblank_irq;
	ops->wait_for_commit_done = dpu_encoder_phys_cmd_wait_for_commit_done;
	ops->prepare_for_kickoff = dpu_encoder_phys_cmd_prepare_for_kickoff;
	ops->wait_for_tx_complete = dpu_encoder_phys_cmd_wait_for_tx_complete;
	ops->wait_for_vblank = dpu_encoder_phys_cmd_wait_for_vblank;
	ops->trigger_start = dpu_encoder_phys_cmd_trigger_start;
	ops->needs_single_flush = dpu_encoder_phys_cmd_needs_single_flush;
	ops->hw_reset = dpu_encoder_helper_hw_reset;
	ops->irq_control = dpu_encoder_phys_cmd_irq_control;
	ops->restore = dpu_encoder_phys_cmd_enable_helper;
	ops->prepare_idle_pc = dpu_encoder_phys_cmd_prepare_idle_pc;
	ops->handle_post_kickoff = dpu_encoder_phys_cmd_handle_post_kickoff;
	ops->get_line_count = dpu_encoder_phys_cmd_get_line_count;
}