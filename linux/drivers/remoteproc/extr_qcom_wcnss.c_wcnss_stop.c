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
struct qcom_wcnss {int /*<<< orphan*/  dev; int /*<<< orphan*/  stop_bit; scalar_t__ state; int /*<<< orphan*/  stop_done; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WCNSS_PAS_ID ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int qcom_scm_pas_shutdown (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qcom_smem_state_update_bits (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wcnss_stop(struct rproc *rproc)
{
	struct qcom_wcnss *wcnss = (struct qcom_wcnss *)rproc->priv;
	int ret;

	if (wcnss->state) {
		qcom_smem_state_update_bits(wcnss->state,
					    BIT(wcnss->stop_bit),
					    BIT(wcnss->stop_bit));

		ret = wait_for_completion_timeout(&wcnss->stop_done,
						  msecs_to_jiffies(5000));
		if (ret == 0)
			dev_err(wcnss->dev, "timed out on wait\n");

		qcom_smem_state_update_bits(wcnss->state,
					    BIT(wcnss->stop_bit),
					    0);
	}

	ret = qcom_scm_pas_shutdown(WCNSS_PAS_ID);
	if (ret)
		dev_err(wcnss->dev, "failed to shutdown: %d\n", ret);

	return ret;
}