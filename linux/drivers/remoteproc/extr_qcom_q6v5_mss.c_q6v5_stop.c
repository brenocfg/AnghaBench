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
struct rproc {scalar_t__ priv; } ;
struct q6v5 {int running; int /*<<< orphan*/  dev; int /*<<< orphan*/  q6v5; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  q6v5_mba_reclaim (struct q6v5*) ; 
 int qcom_q6v5_request_stop (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int q6v5_stop(struct rproc *rproc)
{
	struct q6v5 *qproc = (struct q6v5 *)rproc->priv;
	int ret;

	qproc->running = false;

	ret = qcom_q6v5_request_stop(&qproc->q6v5);
	if (ret == -ETIMEDOUT)
		dev_err(qproc->dev, "timed out on wait\n");

	q6v5_mba_reclaim(qproc);

	return 0;
}