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
struct resource {int /*<<< orphan*/  start; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct mcp_sa11x0 {int mccr0; int /*<<< orphan*/  base0; int /*<<< orphan*/  base1; } ;
struct mcp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int MCCR0_MCE ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mcp_host_del (struct mcp*) ; 
 int /*<<< orphan*/  mcp_host_free (struct mcp*) ; 
 struct mcp* platform_get_drvdata (struct platform_device*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int) ; 
 struct mcp_sa11x0* priv (struct mcp*) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 

__attribute__((used)) static int mcp_sa11x0_remove(struct platform_device *dev)
{
	struct mcp *mcp = platform_get_drvdata(dev);
	struct mcp_sa11x0 *m = priv(mcp);
	struct resource *mem0, *mem1;

	if (m->mccr0 & MCCR0_MCE)
		dev_warn(&dev->dev,
			 "device left active (missing disable call?)\n");

	mem0 = platform_get_resource(dev, IORESOURCE_MEM, 0);
	mem1 = platform_get_resource(dev, IORESOURCE_MEM, 1);

	mcp_host_del(mcp);
	iounmap(m->base1);
	iounmap(m->base0);
	mcp_host_free(mcp);
	release_mem_region(mem1->start, resource_size(mem1));
	release_mem_region(mem0->start, resource_size(mem0));

	return 0;
}