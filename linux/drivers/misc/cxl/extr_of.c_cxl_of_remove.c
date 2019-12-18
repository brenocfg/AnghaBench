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
struct cxl {int slices; int /*<<< orphan*/ * afu; } ;

/* Variables and functions */
 int /*<<< orphan*/  cxl_guest_remove_adapter (struct cxl*) ; 
 int /*<<< orphan*/  cxl_guest_remove_afu (int /*<<< orphan*/ ) ; 
 struct cxl* dev_get_drvdata (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cxl_of_remove(struct platform_device *pdev)
{
	struct cxl *adapter;
	int afu;

	adapter = dev_get_drvdata(&pdev->dev);
	for (afu = 0; afu < adapter->slices; afu++)
		cxl_guest_remove_afu(adapter->afu[afu]);

	cxl_guest_remove_adapter(adapter);
	return 0;
}