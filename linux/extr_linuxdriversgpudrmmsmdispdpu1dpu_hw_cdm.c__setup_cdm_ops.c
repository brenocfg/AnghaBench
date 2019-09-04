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
struct dpu_hw_cdm_ops {int /*<<< orphan*/  disable; int /*<<< orphan*/  enable; int /*<<< orphan*/  setup_cdwn; int /*<<< orphan*/  setup_csc_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  dpu_hw_cdm_disable ; 
 int /*<<< orphan*/  dpu_hw_cdm_enable ; 
 int /*<<< orphan*/  dpu_hw_cdm_setup_cdwn ; 
 int /*<<< orphan*/  dpu_hw_cdm_setup_csc_10bit ; 

__attribute__((used)) static void _setup_cdm_ops(struct dpu_hw_cdm_ops *ops,
	unsigned long features)
{
	ops->setup_csc_data = dpu_hw_cdm_setup_csc_10bit;
	ops->setup_cdwn = dpu_hw_cdm_setup_cdwn;
	ops->enable = dpu_hw_cdm_enable;
	ops->disable = dpu_hw_cdm_disable;
}