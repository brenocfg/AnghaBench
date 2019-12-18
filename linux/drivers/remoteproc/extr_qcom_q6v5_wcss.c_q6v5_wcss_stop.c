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
struct rproc {struct q6v5_wcss* priv; } ;
struct q6v5_wcss {int /*<<< orphan*/  q6v5; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int q6v5_q6_powerdown (struct q6v5_wcss*) ; 
 int q6v5_wcss_powerdown (struct q6v5_wcss*) ; 
 int qcom_q6v5_request_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qcom_q6v5_unprepare (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int q6v5_wcss_stop(struct rproc *rproc)
{
	struct q6v5_wcss *wcss = rproc->priv;
	int ret;

	/* WCSS powerdown */
	ret = qcom_q6v5_request_stop(&wcss->q6v5);
	if (ret == -ETIMEDOUT) {
		dev_err(wcss->dev, "timed out on wait\n");
		return ret;
	}

	ret = q6v5_wcss_powerdown(wcss);
	if (ret)
		return ret;

	/* Q6 Power down */
	ret = q6v5_q6_powerdown(wcss);
	if (ret)
		return ret;

	qcom_q6v5_unprepare(&wcss->q6v5);

	return 0;
}