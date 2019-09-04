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
struct resource {scalar_t__ end; scalar_t__ start; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRVNAME ; 
 int EBUSY ; 
 int ENOENT ; 
 int /*<<< orphan*/  IORESOURCE_IO ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,unsigned long,...) ; 
 int /*<<< orphan*/  devm_request_region (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 

__attribute__((used)) static int pc87427_request_regions(struct platform_device *pdev,
					     int count)
{
	struct resource *res;
	int i;

	for (i = 0; i < count; i++) {
		res = platform_get_resource(pdev, IORESOURCE_IO, i);
		if (!res) {
			dev_err(&pdev->dev, "Missing resource #%d\n", i);
			return -ENOENT;
		}
		if (!devm_request_region(&pdev->dev, res->start,
					 resource_size(res), DRVNAME)) {
			dev_err(&pdev->dev,
				"Failed to request region 0x%lx-0x%lx\n",
				(unsigned long)res->start,
				(unsigned long)res->end);
			return -EBUSY;
		}
	}
	return 0;
}