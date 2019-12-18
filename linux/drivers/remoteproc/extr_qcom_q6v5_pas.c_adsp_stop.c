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
struct qcom_adsp {int /*<<< orphan*/  q6v5; int /*<<< orphan*/  dev; int /*<<< orphan*/  pas_id; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  qcom_pas_handover (int /*<<< orphan*/ *) ; 
 int qcom_q6v5_request_stop (int /*<<< orphan*/ *) ; 
 int qcom_q6v5_unprepare (int /*<<< orphan*/ *) ; 
 int qcom_scm_pas_shutdown (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int adsp_stop(struct rproc *rproc)
{
	struct qcom_adsp *adsp = (struct qcom_adsp *)rproc->priv;
	int handover;
	int ret;

	ret = qcom_q6v5_request_stop(&adsp->q6v5);
	if (ret == -ETIMEDOUT)
		dev_err(adsp->dev, "timed out on wait\n");

	ret = qcom_scm_pas_shutdown(adsp->pas_id);
	if (ret)
		dev_err(adsp->dev, "failed to shutdown: %d\n", ret);

	handover = qcom_q6v5_unprepare(&adsp->q6v5);
	if (handover)
		qcom_pas_handover(&adsp->q6v5);

	return ret;
}