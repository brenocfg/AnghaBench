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
struct platform_device {int dummy; } ;
struct au1550nd_ctx {int /*<<< orphan*/  base; int /*<<< orphan*/  chip; } ;

/* Variables and functions */
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct au1550nd_ctx*) ; 
 int /*<<< orphan*/  nand_release (int /*<<< orphan*/ *) ; 
 struct au1550nd_ctx* platform_get_drvdata (struct platform_device*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int au1550nd_remove(struct platform_device *pdev)
{
	struct au1550nd_ctx *ctx = platform_get_drvdata(pdev);
	struct resource *r = platform_get_resource(pdev, IORESOURCE_MEM, 0);

	nand_release(&ctx->chip);
	iounmap(ctx->base);
	release_mem_region(r->start, 0x1000);
	kfree(ctx);
	return 0;
}