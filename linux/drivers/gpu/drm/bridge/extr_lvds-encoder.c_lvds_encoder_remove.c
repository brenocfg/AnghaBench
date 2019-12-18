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
struct lvds_encoder {int /*<<< orphan*/  bridge; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_bridge_remove (int /*<<< orphan*/ *) ; 
 struct lvds_encoder* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int lvds_encoder_remove(struct platform_device *pdev)
{
	struct lvds_encoder *lvds_encoder = platform_get_drvdata(pdev);

	drm_bridge_remove(&lvds_encoder->bridge);

	return 0;
}