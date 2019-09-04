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
struct msm_gpu {scalar_t__ ebi1_clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_prepare_enable (scalar_t__) ; 

__attribute__((used)) static int enable_axi(struct msm_gpu *gpu)
{
	if (gpu->ebi1_clk)
		clk_prepare_enable(gpu->ebi1_clk);
	return 0;
}