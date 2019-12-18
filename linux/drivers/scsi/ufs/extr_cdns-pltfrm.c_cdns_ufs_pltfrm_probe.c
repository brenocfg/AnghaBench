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
struct ufs_hba_variant_ops {int dummy; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct platform_device {struct device dev; } ;
struct of_device_id {scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  cdns_ufs_of_match ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 struct of_device_id* of_match_node (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ufshcd_pltfrm_init (struct platform_device*,struct ufs_hba_variant_ops*) ; 

__attribute__((used)) static int cdns_ufs_pltfrm_probe(struct platform_device *pdev)
{
	int err;
	const struct of_device_id *of_id;
	struct ufs_hba_variant_ops *vops;
	struct device *dev = &pdev->dev;

	of_id = of_match_node(cdns_ufs_of_match, dev->of_node);
	vops = (struct ufs_hba_variant_ops *)of_id->data;

	/* Perform generic probe */
	err = ufshcd_pltfrm_init(pdev, vops);
	if (err)
		dev_err(dev, "ufshcd_pltfrm_init() failed %d\n", err);

	return err;
}