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
struct fsl_qspi {int /*<<< orphan*/  clk_en; int /*<<< orphan*/  clk; int /*<<< orphan*/  pm_qos_req; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 scalar_t__ needs_wakeup_wait_mode (struct fsl_qspi*) ; 
 int /*<<< orphan*/  pm_qos_remove_request (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fsl_qspi_clk_disable_unprep(struct fsl_qspi *q)
{
	if (needs_wakeup_wait_mode(q))
		pm_qos_remove_request(&q->pm_qos_req);

	clk_disable_unprepare(q->clk);
	clk_disable_unprepare(q->clk_en);
}