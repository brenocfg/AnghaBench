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
struct csc_data {int /*<<< orphan*/  base; int /*<<< orphan*/ * res; struct platform_device* pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENODEV ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct csc_data* ERR_CAST (int /*<<< orphan*/ ) ; 
 struct csc_data* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  devm_ioremap_resource (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct csc_data* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * platform_get_resource_byname (struct platform_device*,int /*<<< orphan*/ ,char const*) ; 

struct csc_data *csc_create(struct platform_device *pdev, const char *res_name)
{
	struct csc_data *csc;

	dev_dbg(&pdev->dev, "csc_create\n");

	csc = devm_kzalloc(&pdev->dev, sizeof(*csc), GFP_KERNEL);
	if (!csc) {
		dev_err(&pdev->dev, "couldn't alloc csc_data\n");
		return ERR_PTR(-ENOMEM);
	}

	csc->pdev = pdev;

	csc->res = platform_get_resource_byname(pdev, IORESOURCE_MEM,
						res_name);
	if (csc->res == NULL) {
		dev_err(&pdev->dev, "missing '%s' platform resources data\n",
			res_name);
		return ERR_PTR(-ENODEV);
	}

	csc->base = devm_ioremap_resource(&pdev->dev, csc->res);
	if (IS_ERR(csc->base)) {
		dev_err(&pdev->dev, "failed to ioremap\n");
		return ERR_CAST(csc->base);
	}

	return csc;
}