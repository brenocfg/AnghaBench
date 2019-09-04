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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct msm_edp {struct platform_device* pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,struct msm_edp*) ; 
 int ENOMEM ; 
 int ENXIO ; 
 struct msm_edp* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct msm_edp* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  edp_destroy (struct platform_device*) ; 
 int msm_edp_ctrl_init (struct msm_edp*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct msm_edp*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static struct msm_edp *edp_init(struct platform_device *pdev)
{
	struct msm_edp *edp = NULL;
	int ret;

	if (!pdev) {
		pr_err("no eDP device\n");
		ret = -ENXIO;
		goto fail;
	}

	edp = devm_kzalloc(&pdev->dev, sizeof(*edp), GFP_KERNEL);
	if (!edp) {
		ret = -ENOMEM;
		goto fail;
	}
	DBG("eDP probed=%p", edp);

	edp->pdev = pdev;
	platform_set_drvdata(pdev, edp);

	ret = msm_edp_ctrl_init(edp);
	if (ret)
		goto fail;

	return edp;

fail:
	if (edp)
		edp_destroy(pdev);

	return ERR_PTR(ret);
}