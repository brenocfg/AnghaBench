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
struct dpu_pingpong_cfg {int dummy; } ;
struct dpu_hw_pingpong_ops {int /*<<< orphan*/  get_line_count; int /*<<< orphan*/  poll_timeout_wr_ptr; int /*<<< orphan*/  get_vsync_info; int /*<<< orphan*/  connect_external_te; int /*<<< orphan*/  enable_tearcheck; int /*<<< orphan*/  setup_tearcheck; } ;

/* Variables and functions */
 int /*<<< orphan*/  dpu_hw_pp_connect_external_te ; 
 int /*<<< orphan*/  dpu_hw_pp_enable_te ; 
 int /*<<< orphan*/  dpu_hw_pp_get_line_count ; 
 int /*<<< orphan*/  dpu_hw_pp_get_vsync_info ; 
 int /*<<< orphan*/  dpu_hw_pp_poll_timeout_wr_ptr ; 
 int /*<<< orphan*/  dpu_hw_pp_setup_te_config ; 

__attribute__((used)) static void _setup_pingpong_ops(struct dpu_hw_pingpong_ops *ops,
	const struct dpu_pingpong_cfg *hw_cap)
{
	ops->setup_tearcheck = dpu_hw_pp_setup_te_config;
	ops->enable_tearcheck = dpu_hw_pp_enable_te;
	ops->connect_external_te = dpu_hw_pp_connect_external_te;
	ops->get_vsync_info = dpu_hw_pp_get_vsync_info;
	ops->poll_timeout_wr_ptr = dpu_hw_pp_poll_timeout_wr_ptr;
	ops->get_line_count = dpu_hw_pp_get_line_count;
}