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
struct TYPE_5__ {scalar_t__ family; } ;
struct TYPE_6__ {TYPE_1__ info; } ;
struct TYPE_7__ {TYPE_2__ device; } ;
struct nouveau_drm {TYPE_3__ client; } ;
struct drm_device {TYPE_4__* pdev; } ;
struct TYPE_8__ {int device; } ;

/* Variables and functions */
 scalar_t__ NV_DEVICE_INFO_V0_KELVIN ; 
 struct nouveau_drm* nouveau_drm (struct drm_device*) ; 
 int /*<<< orphan*/  nv04_update_arb (struct drm_device*,int,int,int*,int*) ; 
 int /*<<< orphan*/  nv20_update_arb (int*,int*) ; 

void
nouveau_calc_arb(struct drm_device *dev, int vclk, int bpp, int *burst, int *lwm)
{
	struct nouveau_drm *drm = nouveau_drm(dev);

	if (drm->client.device.info.family < NV_DEVICE_INFO_V0_KELVIN)
		nv04_update_arb(dev, vclk, bpp, burst, lwm);
	else if ((dev->pdev->device & 0xfff0) == 0x0240 /*CHIPSET_C51*/ ||
		 (dev->pdev->device & 0xfff0) == 0x03d0 /*CHIPSET_C512*/) {
		*burst = 128;
		*lwm = 0x0480;
	} else
		nv20_update_arb(burst, lwm);
}