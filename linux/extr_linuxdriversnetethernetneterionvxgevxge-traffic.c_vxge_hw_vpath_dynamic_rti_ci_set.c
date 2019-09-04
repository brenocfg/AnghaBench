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
typedef  int /*<<< orphan*/  u64 ;
struct __vxge_hw_ring {TYPE_1__* vp_reg; int /*<<< orphan*/  tim_rti_cfg1_saved; } ;
struct TYPE_2__ {int /*<<< orphan*/ * tim_cfg1_int_num; } ;

/* Variables and functions */
 int /*<<< orphan*/  VXGE_HW_TIM_CFG1_INT_NUM_TIMER_CI ; 
 size_t VXGE_HW_VPATH_INTR_RX ; 
 int /*<<< orphan*/  writeq (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void vxge_hw_vpath_dynamic_rti_ci_set(struct __vxge_hw_ring *ring)
{
	u64 val64 = ring->tim_rti_cfg1_saved;

	val64 |= VXGE_HW_TIM_CFG1_INT_NUM_TIMER_CI;
	ring->tim_rti_cfg1_saved = val64;
	writeq(val64, &ring->vp_reg->tim_cfg1_int_num[VXGE_HW_VPATH_INTR_RX]);
}