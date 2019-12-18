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
struct dpu_hw_vbif_ops {int /*<<< orphan*/  set_write_gather_en; int /*<<< orphan*/  clear_errors; int /*<<< orphan*/  set_mem_type; int /*<<< orphan*/  set_qos_remap; int /*<<< orphan*/  get_halt_ctrl; int /*<<< orphan*/  set_halt_ctrl; int /*<<< orphan*/  get_limit_conf; int /*<<< orphan*/  set_limit_conf; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPU_VBIF_QOS_REMAP ; 
 int /*<<< orphan*/  dpu_hw_clear_errors ; 
 int /*<<< orphan*/  dpu_hw_get_halt_ctrl ; 
 int /*<<< orphan*/  dpu_hw_get_limit_conf ; 
 int /*<<< orphan*/  dpu_hw_set_halt_ctrl ; 
 int /*<<< orphan*/  dpu_hw_set_limit_conf ; 
 int /*<<< orphan*/  dpu_hw_set_mem_type ; 
 int /*<<< orphan*/  dpu_hw_set_qos_remap ; 
 int /*<<< orphan*/  dpu_hw_set_write_gather_en ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,unsigned long*) ; 

__attribute__((used)) static void _setup_vbif_ops(struct dpu_hw_vbif_ops *ops,
		unsigned long cap)
{
	ops->set_limit_conf = dpu_hw_set_limit_conf;
	ops->get_limit_conf = dpu_hw_get_limit_conf;
	ops->set_halt_ctrl = dpu_hw_set_halt_ctrl;
	ops->get_halt_ctrl = dpu_hw_get_halt_ctrl;
	if (test_bit(DPU_VBIF_QOS_REMAP, &cap))
		ops->set_qos_remap = dpu_hw_set_qos_remap;
	ops->set_mem_type = dpu_hw_set_mem_type;
	ops->clear_errors = dpu_hw_clear_errors;
	ops->set_write_gather_en = dpu_hw_set_write_gather_en;
}