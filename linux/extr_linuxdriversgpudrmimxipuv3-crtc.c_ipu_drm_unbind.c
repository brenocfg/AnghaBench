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
struct ipu_crtc {scalar_t__* plane; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct ipu_crtc* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  ipu_plane_put_resources (scalar_t__) ; 
 int /*<<< orphan*/  ipu_put_resources (struct ipu_crtc*) ; 

__attribute__((used)) static void ipu_drm_unbind(struct device *dev, struct device *master,
	void *data)
{
	struct ipu_crtc *ipu_crtc = dev_get_drvdata(dev);

	ipu_put_resources(ipu_crtc);
	if (ipu_crtc->plane[1])
		ipu_plane_put_resources(ipu_crtc->plane[1]);
	ipu_plane_put_resources(ipu_crtc->plane[0]);
}