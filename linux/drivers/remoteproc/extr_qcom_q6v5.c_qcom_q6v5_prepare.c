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
struct qcom_q6v5 {int running; int handover_issued; int /*<<< orphan*/  handover_irq; int /*<<< orphan*/  stop_done; int /*<<< orphan*/  start_done; } ;

/* Variables and functions */
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 

int qcom_q6v5_prepare(struct qcom_q6v5 *q6v5)
{
	reinit_completion(&q6v5->start_done);
	reinit_completion(&q6v5->stop_done);

	q6v5->running = true;
	q6v5->handover_issued = false;

	enable_irq(q6v5->handover_irq);

	return 0;
}