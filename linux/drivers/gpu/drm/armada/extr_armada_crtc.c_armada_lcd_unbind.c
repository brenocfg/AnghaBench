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
struct device {int dummy; } ;
struct armada_crtc {int /*<<< orphan*/  crtc; } ;

/* Variables and functions */
 int /*<<< orphan*/  armada_drm_crtc_destroy (int /*<<< orphan*/ *) ; 
 struct armada_crtc* dev_get_drvdata (struct device*) ; 

__attribute__((used)) static void
armada_lcd_unbind(struct device *dev, struct device *master, void *data)
{
	struct armada_crtc *dcrtc = dev_get_drvdata(dev);

	armada_drm_crtc_destroy(&dcrtc->crtc);
}