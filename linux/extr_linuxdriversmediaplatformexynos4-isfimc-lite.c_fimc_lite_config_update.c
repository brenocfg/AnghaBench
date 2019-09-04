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
struct fimc_lite {int /*<<< orphan*/  state; TYPE_1__* test_pattern; int /*<<< orphan*/  out_frame; int /*<<< orphan*/  inp_frame; } ;
struct TYPE_2__ {int /*<<< orphan*/  val; } ;

/* Variables and functions */
 int /*<<< orphan*/  ST_FLITE_CONFIG ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flite_hw_set_dma_window (struct fimc_lite*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flite_hw_set_test_pattern (struct fimc_lite*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flite_hw_set_window_offset (struct fimc_lite*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fimc_lite_config_update(struct fimc_lite *fimc)
{
	flite_hw_set_window_offset(fimc, &fimc->inp_frame);
	flite_hw_set_dma_window(fimc, &fimc->out_frame);
	flite_hw_set_test_pattern(fimc, fimc->test_pattern->val);
	clear_bit(ST_FLITE_CONFIG, &fimc->state);
}