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
struct vc4_dpi {int /*<<< orphan*/  core_clock; int /*<<< orphan*/  encoder; } ;
struct vc4_dev {int /*<<< orphan*/ * dpi; } ;
struct drm_device {int dummy; } ;
struct device {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 void* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  drm_encoder_cleanup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_of_panel_bridge_remove (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct vc4_dev* to_vc4_dev (struct drm_device*) ; 

__attribute__((used)) static void vc4_dpi_unbind(struct device *dev, struct device *master,
			   void *data)
{
	struct drm_device *drm = dev_get_drvdata(master);
	struct vc4_dev *vc4 = to_vc4_dev(drm);
	struct vc4_dpi *dpi = dev_get_drvdata(dev);

	drm_of_panel_bridge_remove(dev->of_node, 0, 0);

	drm_encoder_cleanup(dpi->encoder);

	clk_disable_unprepare(dpi->core_clock);

	vc4->dpi = NULL;
}