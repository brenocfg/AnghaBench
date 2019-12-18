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
struct qcom_adsp {int /*<<< orphan*/  rproc; int /*<<< orphan*/  ssr_subdev; int /*<<< orphan*/  smd_subdev; int /*<<< orphan*/  sysmon; int /*<<< orphan*/  glink_subdev; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 struct qcom_adsp* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  qcom_remove_glink_subdev (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qcom_remove_smd_subdev (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qcom_remove_ssr_subdev (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qcom_remove_sysmon_subdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rproc_del (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rproc_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int adsp_remove(struct platform_device *pdev)
{
	struct qcom_adsp *adsp = platform_get_drvdata(pdev);

	rproc_del(adsp->rproc);

	qcom_remove_glink_subdev(adsp->rproc, &adsp->glink_subdev);
	qcom_remove_sysmon_subdev(adsp->sysmon);
	qcom_remove_smd_subdev(adsp->rproc, &adsp->smd_subdev);
	qcom_remove_ssr_subdev(adsp->rproc, &adsp->ssr_subdev);
	rproc_free(adsp->rproc);

	return 0;
}