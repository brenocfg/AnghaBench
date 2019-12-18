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
struct vc4_dsi {int port; int /*<<< orphan*/  encoder; scalar_t__ bridge; } ;
struct vc4_dev {int /*<<< orphan*/ * dsi1; } ;
struct drm_device {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 void* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (struct device*) ; 
 struct vc4_dev* to_vc4_dev (struct drm_device*) ; 
 int /*<<< orphan*/  vc4_dsi_encoder_destroy (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vc4_dsi_unbind(struct device *dev, struct device *master,
			   void *data)
{
	struct drm_device *drm = dev_get_drvdata(master);
	struct vc4_dev *vc4 = to_vc4_dev(drm);
	struct vc4_dsi *dsi = dev_get_drvdata(dev);

	if (dsi->bridge)
		pm_runtime_disable(dev);

	vc4_dsi_encoder_destroy(dsi->encoder);

	if (dsi->port == 1)
		vc4->dsi1 = NULL;
}