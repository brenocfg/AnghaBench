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
struct s3c_camif_plat_data {int /*<<< orphan*/  (* gpio_put ) () ;} ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct camif_dev {int /*<<< orphan*/  v4l2_dev; int /*<<< orphan*/  media_dev; struct s3c_camif_plat_data pdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  camif_clk_put (struct camif_dev*) ; 
 int /*<<< orphan*/  camif_unregister_media_entities (struct camif_dev*) ; 
 int /*<<< orphan*/  media_device_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  media_device_unregister (int /*<<< orphan*/ *) ; 
 struct camif_dev* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 () ; 
 int /*<<< orphan*/  v4l2_device_unregister (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int s3c_camif_remove(struct platform_device *pdev)
{
	struct camif_dev *camif = platform_get_drvdata(pdev);
	struct s3c_camif_plat_data *pdata = &camif->pdata;

	media_device_unregister(&camif->media_dev);
	media_device_cleanup(&camif->media_dev);
	camif_unregister_media_entities(camif);
	v4l2_device_unregister(&camif->v4l2_dev);

	pm_runtime_disable(&pdev->dev);
	camif_clk_put(camif);
	pdata->gpio_put();

	return 0;
}