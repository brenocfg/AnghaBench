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
struct dpu_hw_intf_ops {int /*<<< orphan*/  get_line_count; int /*<<< orphan*/  collect_misr; int /*<<< orphan*/  setup_misr; int /*<<< orphan*/  enable_timing; int /*<<< orphan*/  get_status; int /*<<< orphan*/  setup_prg_fetch; int /*<<< orphan*/  setup_timing_gen; } ;

/* Variables and functions */
 int /*<<< orphan*/  dpu_hw_intf_collect_misr ; 
 int /*<<< orphan*/  dpu_hw_intf_enable_timing_engine ; 
 int /*<<< orphan*/  dpu_hw_intf_get_line_count ; 
 int /*<<< orphan*/  dpu_hw_intf_get_status ; 
 int /*<<< orphan*/  dpu_hw_intf_setup_misr ; 
 int /*<<< orphan*/  dpu_hw_intf_setup_prg_fetch ; 
 int /*<<< orphan*/  dpu_hw_intf_setup_timing_engine ; 

__attribute__((used)) static void _setup_intf_ops(struct dpu_hw_intf_ops *ops,
		unsigned long cap)
{
	ops->setup_timing_gen = dpu_hw_intf_setup_timing_engine;
	ops->setup_prg_fetch  = dpu_hw_intf_setup_prg_fetch;
	ops->get_status = dpu_hw_intf_get_status;
	ops->enable_timing = dpu_hw_intf_enable_timing_engine;
	ops->setup_misr = dpu_hw_intf_setup_misr;
	ops->collect_misr = dpu_hw_intf_collect_misr;
	ops->get_line_count = dpu_hw_intf_get_line_count;
}