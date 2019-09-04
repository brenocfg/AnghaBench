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
struct sc_data {int /*<<< orphan*/  base; int /*<<< orphan*/  res; struct platform_device* pdev; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENODEV ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct sc_data* ERR_CAST (int /*<<< orphan*/ ) ; 
 struct sc_data* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  devm_ioremap_resource (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct sc_data* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_get_resource_byname (struct platform_device*,int /*<<< orphan*/ ,char const*) ; 

struct sc_data *sc_create(struct platform_device *pdev, const char *res_name)
{
	struct sc_data *sc;

	dev_dbg(&pdev->dev, "sc_create\n");

	sc = devm_kzalloc(&pdev->dev, sizeof(*sc), GFP_KERNEL);
	if (!sc) {
		dev_err(&pdev->dev, "couldn't alloc sc_data\n");
		return ERR_PTR(-ENOMEM);
	}

	sc->pdev = pdev;

	sc->res = platform_get_resource_byname(pdev, IORESOURCE_MEM, res_name);
	if (!sc->res) {
		dev_err(&pdev->dev, "missing '%s' platform resources data\n",
			res_name);
		return ERR_PTR(-ENODEV);
	}

	sc->base = devm_ioremap_resource(&pdev->dev, sc->res);
	if (IS_ERR(sc->base)) {
		dev_err(&pdev->dev, "failed to ioremap\n");
		return ERR_CAST(sc->base);
	}

	return sc;
}