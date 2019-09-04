#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sh_tmu_device {int /*<<< orphan*/ * mapbase; TYPE_1__* pdev; } ;
struct resource {int /*<<< orphan*/  start; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * ioremap_nocache (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 

__attribute__((used)) static int sh_tmu_map_memory(struct sh_tmu_device *tmu)
{
	struct resource *res;

	res = platform_get_resource(tmu->pdev, IORESOURCE_MEM, 0);
	if (!res) {
		dev_err(&tmu->pdev->dev, "failed to get I/O memory\n");
		return -ENXIO;
	}

	tmu->mapbase = ioremap_nocache(res->start, resource_size(res));
	if (tmu->mapbase == NULL)
		return -ENXIO;

	return 0;
}