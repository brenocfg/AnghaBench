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
struct TYPE_2__ {int /*<<< orphan*/  (* trigger_start ) (struct dpu_encoder_phys*) ;} ;
struct dpu_encoder_phys {scalar_t__ enable_state; TYPE_1__ ops; int /*<<< orphan*/  hw_pp; } ;

/* Variables and functions */
 scalar_t__ DPU_ENC_DISABLED ; 
 int /*<<< orphan*/  DPU_ERROR (char*) ; 
 int /*<<< orphan*/  stub1 (struct dpu_encoder_phys*) ; 

__attribute__((used)) static void _dpu_encoder_trigger_start(struct dpu_encoder_phys *phys)
{
	if (!phys) {
		DPU_ERROR("invalid argument(s)\n");
		return;
	}

	if (!phys->hw_pp) {
		DPU_ERROR("invalid pingpong hw\n");
		return;
	}

	if (phys->ops.trigger_start && phys->enable_state != DPU_ENC_DISABLED)
		phys->ops.trigger_start(phys);
}