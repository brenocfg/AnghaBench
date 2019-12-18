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
struct keystone_rproc {int /*<<< orphan*/  rproc; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  RPROC_FATAL_ERROR ; 
 int /*<<< orphan*/  rproc_report_crash (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t keystone_rproc_exception_interrupt(int irq, void *dev_id)
{
	struct keystone_rproc *ksproc = dev_id;

	rproc_report_crash(ksproc->rproc, RPROC_FATAL_ERROR);

	return IRQ_HANDLED;
}