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
struct fsl_qspi {int /*<<< orphan*/  pm_qos_req; int /*<<< orphan*/  clk_en; int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  PM_QOS_CPU_DMA_LATENCY ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 scalar_t__ needs_wakeup_wait_mode (struct fsl_qspi*) ; 
 int /*<<< orphan*/  pm_qos_add_request (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fsl_qspi_clk_prep_enable(struct fsl_qspi *q)
{
	int ret;

	ret = clk_prepare_enable(q->clk_en);
	if (ret)
		return ret;

	ret = clk_prepare_enable(q->clk);
	if (ret) {
		clk_disable_unprepare(q->clk_en);
		return ret;
	}

	if (needs_wakeup_wait_mode(q))
		pm_qos_add_request(&q->pm_qos_req, PM_QOS_CPU_DMA_LATENCY, 0);

	return 0;
}