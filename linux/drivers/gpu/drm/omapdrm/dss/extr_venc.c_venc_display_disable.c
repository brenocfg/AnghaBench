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
struct venc_device {int /*<<< orphan*/  venc_lock; } ;
struct omap_dss_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSSDBG (char*) ; 
 struct venc_device* dssdev_to_venc (struct omap_dss_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  venc_power_off (struct venc_device*) ; 

__attribute__((used)) static void venc_display_disable(struct omap_dss_device *dssdev)
{
	struct venc_device *venc = dssdev_to_venc(dssdev);

	DSSDBG("venc_display_disable\n");

	mutex_lock(&venc->venc_lock);

	venc_power_off(venc);

	mutex_unlock(&venc->venc_lock);
}