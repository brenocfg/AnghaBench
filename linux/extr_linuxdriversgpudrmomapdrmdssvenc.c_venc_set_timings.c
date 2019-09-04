#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct videomode {int dummy; } ;
struct venc_device {int /*<<< orphan*/  venc_lock; TYPE_1__* dss; struct videomode vm; scalar_t__ wss_data; } ;
struct omap_dss_device {int dummy; } ;
typedef  int /*<<< orphan*/  actual_vm ;
struct TYPE_2__ {int /*<<< orphan*/  dispc; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSSDBG (char*) ; 
#define  VENC_MODE_NTSC 129 
#define  VENC_MODE_PAL 128 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  dispc_set_tv_pclk (int /*<<< orphan*/ ,int) ; 
 struct venc_device* dssdev_to_venc (struct omap_dss_device*) ; 
 scalar_t__ memcmp (struct videomode*,struct videomode*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct videomode omap_dss_ntsc_vm ; 
 struct videomode omap_dss_pal_vm ; 
 int venc_get_videomode (struct videomode*) ; 

__attribute__((used)) static void venc_set_timings(struct omap_dss_device *dssdev,
			     struct videomode *vm)
{
	struct venc_device *venc = dssdev_to_venc(dssdev);
	struct videomode actual_vm;

	DSSDBG("venc_set_timings\n");

	mutex_lock(&venc->venc_lock);

	switch (venc_get_videomode(vm)) {
	default:
		WARN_ON_ONCE(1);
	case VENC_MODE_PAL:
		actual_vm = omap_dss_pal_vm;
		break;
	case VENC_MODE_NTSC:
		actual_vm = omap_dss_ntsc_vm;
		break;
	}

	/* Reset WSS data when the TV standard changes. */
	if (memcmp(&venc->vm, &actual_vm, sizeof(actual_vm)))
		venc->wss_data = 0;

	venc->vm = actual_vm;

	dispc_set_tv_pclk(venc->dss->dispc, 13500000);

	mutex_unlock(&venc->venc_lock);
}