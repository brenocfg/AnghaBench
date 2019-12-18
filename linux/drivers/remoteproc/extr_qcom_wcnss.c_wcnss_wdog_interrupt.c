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
struct qcom_wcnss {int /*<<< orphan*/  rproc; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  RPROC_WATCHDOG ; 
 int /*<<< orphan*/  rproc_report_crash (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t wcnss_wdog_interrupt(int irq, void *dev)
{
	struct qcom_wcnss *wcnss = dev;

	rproc_report_crash(wcnss->rproc, RPROC_WATCHDOG);

	return IRQ_HANDLED;
}