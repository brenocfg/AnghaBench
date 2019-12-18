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
struct q6v5 {int /*<<< orphan*/  rproc; int /*<<< orphan*/  proxy_pd_count; int /*<<< orphan*/  proxy_pds; int /*<<< orphan*/  active_pd_count; int /*<<< orphan*/  active_pds; int /*<<< orphan*/  ssr_subdev; int /*<<< orphan*/  smd_subdev; int /*<<< orphan*/  glink_subdev; int /*<<< orphan*/  sysmon; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 struct q6v5* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  q6v5_pds_detach (struct q6v5*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qcom_remove_glink_subdev (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qcom_remove_smd_subdev (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qcom_remove_ssr_subdev (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qcom_remove_sysmon_subdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rproc_del (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rproc_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int q6v5_remove(struct platform_device *pdev)
{
	struct q6v5 *qproc = platform_get_drvdata(pdev);

	rproc_del(qproc->rproc);

	qcom_remove_sysmon_subdev(qproc->sysmon);
	qcom_remove_glink_subdev(qproc->rproc, &qproc->glink_subdev);
	qcom_remove_smd_subdev(qproc->rproc, &qproc->smd_subdev);
	qcom_remove_ssr_subdev(qproc->rproc, &qproc->ssr_subdev);

	q6v5_pds_detach(qproc, qproc->active_pds, qproc->active_pd_count);
	q6v5_pds_detach(qproc, qproc->proxy_pds, qproc->proxy_pd_count);

	rproc_free(qproc->rproc);

	return 0;
}