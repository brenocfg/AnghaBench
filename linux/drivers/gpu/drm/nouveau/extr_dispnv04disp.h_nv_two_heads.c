#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ family; } ;
struct TYPE_7__ {TYPE_2__ info; } ;
struct TYPE_8__ {TYPE_3__ device; } ;
struct nouveau_drm {TYPE_4__ client; } ;
struct drm_device {TYPE_1__* pdev; } ;
struct TYPE_5__ {int device; } ;

/* Variables and functions */
 scalar_t__ NV_DEVICE_INFO_V0_CELSIUS ; 
 struct nouveau_drm* nouveau_drm (struct drm_device*) ; 

__attribute__((used)) static inline bool
nv_two_heads(struct drm_device *dev)
{
	struct nouveau_drm *drm = nouveau_drm(dev);
	const int impl = dev->pdev->device & 0x0ff0;

	if (drm->client.device.info.family >= NV_DEVICE_INFO_V0_CELSIUS && impl != 0x0100 &&
	    impl != 0x0150 && impl != 0x01a0 && impl != 0x0200)
		return true;

	return false;
}