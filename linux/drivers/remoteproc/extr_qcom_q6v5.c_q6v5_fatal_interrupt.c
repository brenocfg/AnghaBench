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
struct qcom_q6v5 {int running; int /*<<< orphan*/  rproc; int /*<<< orphan*/  dev; int /*<<< orphan*/  crash_reason; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IS_ERR (char*) ; 
 int /*<<< orphan*/  QCOM_SMEM_HOST_ANY ; 
 int /*<<< orphan*/  RPROC_FATAL_ERROR ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 char* qcom_smem_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t*) ; 
 int /*<<< orphan*/  rproc_report_crash (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t q6v5_fatal_interrupt(int irq, void *data)
{
	struct qcom_q6v5 *q6v5 = data;
	size_t len;
	char *msg;

	msg = qcom_smem_get(QCOM_SMEM_HOST_ANY, q6v5->crash_reason, &len);
	if (!IS_ERR(msg) && len > 0 && msg[0])
		dev_err(q6v5->dev, "fatal error received: %s\n", msg);
	else
		dev_err(q6v5->dev, "fatal error without message\n");

	q6v5->running = false;
	rproc_report_crash(q6v5->rproc, RPROC_FATAL_ERROR);

	return IRQ_HANDLED;
}