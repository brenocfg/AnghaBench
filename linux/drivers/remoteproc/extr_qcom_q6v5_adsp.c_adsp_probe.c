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
struct qcom_adsp {int /*<<< orphan*/ * dev; int /*<<< orphan*/  sysmon; int /*<<< orphan*/  ssr_subdev; int /*<<< orphan*/  glink_subdev; int /*<<< orphan*/  q6v5; struct rproc* rproc; } ;
struct platform_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  name; } ;
struct adsp_pil_data {int /*<<< orphan*/  ssctl_id; int /*<<< orphan*/  sysmon_name; int /*<<< orphan*/  ssr_name; int /*<<< orphan*/  crash_reason_smem; int /*<<< orphan*/  clk_ids; int /*<<< orphan*/  firmware_name; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int adsp_alloc_memory_region (struct qcom_adsp*) ; 
 int adsp_init_clock (struct qcom_adsp*,int /*<<< orphan*/ ) ; 
 int adsp_init_mmio (struct qcom_adsp*,struct platform_device*) ; 
 int adsp_init_reset (struct qcom_adsp*) ; 
 int /*<<< orphan*/  adsp_ops ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct adsp_pil_data* of_device_get_match_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct qcom_adsp*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qcom_add_glink_subdev (struct rproc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qcom_add_ssr_subdev (struct rproc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qcom_add_sysmon_subdev (struct rproc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qcom_adsp_pil_handover ; 
 int qcom_q6v5_init (int /*<<< orphan*/ *,struct platform_device*,struct rproc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rproc_add (struct rproc*) ; 
 struct rproc* rproc_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rproc_free (struct rproc*) ; 

__attribute__((used)) static int adsp_probe(struct platform_device *pdev)
{
	const struct adsp_pil_data *desc;
	struct qcom_adsp *adsp;
	struct rproc *rproc;
	int ret;

	desc = of_device_get_match_data(&pdev->dev);
	if (!desc)
		return -EINVAL;

	rproc = rproc_alloc(&pdev->dev, pdev->name, &adsp_ops,
			    desc->firmware_name, sizeof(*adsp));
	if (!rproc) {
		dev_err(&pdev->dev, "unable to allocate remoteproc\n");
		return -ENOMEM;
	}

	adsp = (struct qcom_adsp *)rproc->priv;
	adsp->dev = &pdev->dev;
	adsp->rproc = rproc;
	platform_set_drvdata(pdev, adsp);

	ret = adsp_alloc_memory_region(adsp);
	if (ret)
		goto free_rproc;

	ret = adsp_init_clock(adsp, desc->clk_ids);
	if (ret)
		goto free_rproc;

	pm_runtime_enable(adsp->dev);

	ret = adsp_init_reset(adsp);
	if (ret)
		goto disable_pm;

	ret = adsp_init_mmio(adsp, pdev);
	if (ret)
		goto disable_pm;

	ret = qcom_q6v5_init(&adsp->q6v5, pdev, rproc, desc->crash_reason_smem,
			     qcom_adsp_pil_handover);
	if (ret)
		goto disable_pm;

	qcom_add_glink_subdev(rproc, &adsp->glink_subdev);
	qcom_add_ssr_subdev(rproc, &adsp->ssr_subdev, desc->ssr_name);
	adsp->sysmon = qcom_add_sysmon_subdev(rproc,
					      desc->sysmon_name,
					      desc->ssctl_id);
	if (IS_ERR(adsp->sysmon)) {
		ret = PTR_ERR(adsp->sysmon);
		goto disable_pm;
	}

	ret = rproc_add(rproc);
	if (ret)
		goto disable_pm;

	return 0;

disable_pm:
	pm_runtime_disable(adsp->dev);
free_rproc:
	rproc_free(rproc);

	return ret;
}