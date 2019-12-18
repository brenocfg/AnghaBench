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
struct hantro_dev {TYPE_1__* clocks; } ;
struct TYPE_2__ {int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  RK3399_ACLK_MAX_FREQ ; 
 int /*<<< orphan*/  clk_set_rate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rk3399_vpu_hw_init(struct hantro_dev *vpu)
{
	/* Bump ACLK to max. possible freq. to improve performance. */
	clk_set_rate(vpu->clocks[0].clk, RK3399_ACLK_MAX_FREQ);
	return 0;
}