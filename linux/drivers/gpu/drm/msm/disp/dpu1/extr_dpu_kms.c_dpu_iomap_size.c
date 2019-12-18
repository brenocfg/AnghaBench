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
struct resource {int dummy; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,char const*) ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 struct resource* platform_get_resource_byname (struct platform_device*,int /*<<< orphan*/ ,char const*) ; 
 unsigned long resource_size (struct resource*) ; 

__attribute__((used)) static unsigned long dpu_iomap_size(struct platform_device *pdev,
				    const char *name)
{
	struct resource *res;

	res = platform_get_resource_byname(pdev, IORESOURCE_MEM, name);
	if (!res) {
		DRM_ERROR("failed to get memory resource: %s\n", name);
		return 0;
	}

	return resource_size(res);
}