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
struct platform_device {int dummy; } ;
struct omap2430_glue {int /*<<< orphan*/  dev; int /*<<< orphan*/  musb; } ;

/* Variables and functions */
 int /*<<< orphan*/  platform_device_unregister (int /*<<< orphan*/ ) ; 
 struct omap2430_glue* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int omap2430_remove(struct platform_device *pdev)
{
	struct omap2430_glue *glue = platform_get_drvdata(pdev);

	platform_device_unregister(glue->musb);
	pm_runtime_disable(glue->dev);

	return 0;
}