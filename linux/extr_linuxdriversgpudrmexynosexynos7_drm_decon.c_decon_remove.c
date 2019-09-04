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
struct decon_context {int /*<<< orphan*/  regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  component_del (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  decon_component_ops ; 
 struct decon_context* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int decon_remove(struct platform_device *pdev)
{
	struct decon_context *ctx = dev_get_drvdata(&pdev->dev);

	pm_runtime_disable(&pdev->dev);

	iounmap(ctx->regs);

	component_del(&pdev->dev, &decon_component_ops);

	return 0;
}