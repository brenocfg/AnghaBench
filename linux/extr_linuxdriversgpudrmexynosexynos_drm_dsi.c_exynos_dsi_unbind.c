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
struct exynos_dsi {int /*<<< orphan*/  dsi_host; } ;
struct drm_encoder {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct drm_encoder* dev_get_drvdata (struct device*) ; 
 struct exynos_dsi* encoder_to_dsi (struct drm_encoder*) ; 
 int /*<<< orphan*/  exynos_dsi_disable (struct drm_encoder*) ; 
 int /*<<< orphan*/  mipi_dsi_host_unregister (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void exynos_dsi_unbind(struct device *dev, struct device *master,
				void *data)
{
	struct drm_encoder *encoder = dev_get_drvdata(dev);
	struct exynos_dsi *dsi = encoder_to_dsi(encoder);

	exynos_dsi_disable(encoder);

	mipi_dsi_host_unregister(&dsi->dsi_host);
}