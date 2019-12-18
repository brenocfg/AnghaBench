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
struct wkup_m3_rproc {struct platform_device* pdev; } ;
struct wkup_m3_platform_data {int /*<<< orphan*/  reset_name; scalar_t__ (* assert_reset ) (struct platform_device*,int /*<<< orphan*/ ) ;} ;
struct rproc {struct wkup_m3_rproc* priv; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct wkup_m3_platform_data* dev_get_platdata (struct device*) ; 
 scalar_t__ stub1 (struct platform_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wkup_m3_rproc_stop(struct rproc *rproc)
{
	struct wkup_m3_rproc *wkupm3 = rproc->priv;
	struct platform_device *pdev = wkupm3->pdev;
	struct device *dev = &pdev->dev;
	struct wkup_m3_platform_data *pdata = dev_get_platdata(dev);

	if (pdata->assert_reset(pdev, pdata->reset_name)) {
		dev_err(dev, "Unable to assert reset of wkup_m3!\n");
		return -ENODEV;
	}

	return 0;
}