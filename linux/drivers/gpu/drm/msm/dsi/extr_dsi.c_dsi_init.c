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
struct msm_dsi {int id; struct platform_device* pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,struct msm_dsi*) ; 
 int ENOMEM ; 
 int ENXIO ; 
 struct msm_dsi* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct msm_dsi* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsi_destroy (struct msm_dsi*) ; 
 int dsi_get_phy (struct msm_dsi*) ; 
 int msm_dsi_host_init (struct msm_dsi*) ; 
 int msm_dsi_manager_register (struct msm_dsi*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct msm_dsi*) ; 

__attribute__((used)) static struct msm_dsi *dsi_init(struct platform_device *pdev)
{
	struct msm_dsi *msm_dsi;
	int ret;

	if (!pdev)
		return ERR_PTR(-ENXIO);

	msm_dsi = devm_kzalloc(&pdev->dev, sizeof(*msm_dsi), GFP_KERNEL);
	if (!msm_dsi)
		return ERR_PTR(-ENOMEM);
	DBG("dsi probed=%p", msm_dsi);

	msm_dsi->id = -1;
	msm_dsi->pdev = pdev;
	platform_set_drvdata(pdev, msm_dsi);

	/* Init dsi host */
	ret = msm_dsi_host_init(msm_dsi);
	if (ret)
		goto destroy_dsi;

	/* GET dsi PHY */
	ret = dsi_get_phy(msm_dsi);
	if (ret)
		goto destroy_dsi;

	/* Register to dsi manager */
	ret = msm_dsi_manager_register(msm_dsi);
	if (ret)
		goto destroy_dsi;

	return msm_dsi;

destroy_dsi:
	dsi_destroy(msm_dsi);
	return ERR_PTR(ret);
}