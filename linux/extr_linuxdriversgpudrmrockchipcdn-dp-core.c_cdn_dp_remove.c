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
struct cdn_dp_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  audio_pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  cdn_dp_component_ops ; 
 int /*<<< orphan*/  cdn_dp_suspend (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  component_del (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platform_device_unregister (int /*<<< orphan*/ ) ; 
 struct cdn_dp_device* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int cdn_dp_remove(struct platform_device *pdev)
{
	struct cdn_dp_device *dp = platform_get_drvdata(pdev);

	platform_device_unregister(dp->audio_pdev);
	cdn_dp_suspend(dp->dev);
	component_del(&pdev->dev, &cdn_dp_component_ops);

	return 0;
}