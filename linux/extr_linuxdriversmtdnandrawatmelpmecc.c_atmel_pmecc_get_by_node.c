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
struct device_node {int dummy; } ;
struct device {int dummy; } ;
struct atmel_pmecc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  EPROBE_DEFER ; 
 struct atmel_pmecc* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  devm_atmel_pmecc_put ; 
 int /*<<< orphan*/  devres_add (struct device*,struct atmel_pmecc**) ; 
 struct atmel_pmecc** devres_alloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_device (int /*<<< orphan*/ *) ; 
 struct platform_device* of_find_device_by_node (struct device_node*) ; 
 struct atmel_pmecc* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static struct atmel_pmecc *atmel_pmecc_get_by_node(struct device *userdev,
						   struct device_node *np)
{
	struct platform_device *pdev;
	struct atmel_pmecc *pmecc, **ptr;

	pdev = of_find_device_by_node(np);
	if (!pdev || !platform_get_drvdata(pdev))
		return ERR_PTR(-EPROBE_DEFER);

	ptr = devres_alloc(devm_atmel_pmecc_put, sizeof(*ptr), GFP_KERNEL);
	if (!ptr)
		return ERR_PTR(-ENOMEM);

	get_device(&pdev->dev);
	pmecc = platform_get_drvdata(pdev);

	*ptr = pmecc;

	devres_add(userdev, ptr);

	return pmecc;
}