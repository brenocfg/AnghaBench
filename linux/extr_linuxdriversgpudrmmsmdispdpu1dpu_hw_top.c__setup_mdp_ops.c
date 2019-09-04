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
struct dpu_hw_mdp_ops {int /*<<< orphan*/  intf_audio_select; int /*<<< orphan*/  reset_ubwc; int /*<<< orphan*/  get_safe_status; int /*<<< orphan*/  setup_vsync_source; int /*<<< orphan*/  get_danger_status; int /*<<< orphan*/  setup_clk_force_ctrl; int /*<<< orphan*/  setup_cdm_output; int /*<<< orphan*/  setup_split_pipe; } ;

/* Variables and functions */
 int /*<<< orphan*/  dpu_hw_get_danger_status ; 
 int /*<<< orphan*/  dpu_hw_get_safe_status ; 
 int /*<<< orphan*/  dpu_hw_intf_audio_select ; 
 int /*<<< orphan*/  dpu_hw_reset_ubwc ; 
 int /*<<< orphan*/  dpu_hw_setup_cdm_output ; 
 int /*<<< orphan*/  dpu_hw_setup_clk_force_ctrl ; 
 int /*<<< orphan*/  dpu_hw_setup_split_pipe ; 
 int /*<<< orphan*/  dpu_hw_setup_vsync_source ; 

__attribute__((used)) static void _setup_mdp_ops(struct dpu_hw_mdp_ops *ops,
		unsigned long cap)
{
	ops->setup_split_pipe = dpu_hw_setup_split_pipe;
	ops->setup_cdm_output = dpu_hw_setup_cdm_output;
	ops->setup_clk_force_ctrl = dpu_hw_setup_clk_force_ctrl;
	ops->get_danger_status = dpu_hw_get_danger_status;
	ops->setup_vsync_source = dpu_hw_setup_vsync_source;
	ops->get_safe_status = dpu_hw_get_safe_status;
	ops->reset_ubwc = dpu_hw_reset_ubwc;
	ops->intf_audio_select = dpu_hw_intf_audio_select;
}