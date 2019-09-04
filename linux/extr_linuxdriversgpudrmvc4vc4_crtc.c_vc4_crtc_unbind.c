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
struct vc4_crtc {int /*<<< orphan*/  base; } ;
struct platform_device {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRTC_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PV_INTEN ; 
 struct vc4_crtc* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,int /*<<< orphan*/ *) ; 
 struct platform_device* to_platform_device (struct device*) ; 
 int /*<<< orphan*/  vc4_crtc_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vc4_crtc_unbind(struct device *dev, struct device *master,
			    void *data)
{
	struct platform_device *pdev = to_platform_device(dev);
	struct vc4_crtc *vc4_crtc = dev_get_drvdata(dev);

	vc4_crtc_destroy(&vc4_crtc->base);

	CRTC_WRITE(PV_INTEN, 0);

	platform_set_drvdata(pdev, NULL);
}