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
struct tilcdc_drm_private {int /*<<< orphan*/  crtc; } ;
struct drm_device {struct tilcdc_drm_private* dev_private; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  tilcdc_crtc_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t tilcdc_irq(int irq, void *arg)
{
	struct drm_device *dev = arg;
	struct tilcdc_drm_private *priv = dev->dev_private;
	return tilcdc_crtc_irq(priv->crtc);
}