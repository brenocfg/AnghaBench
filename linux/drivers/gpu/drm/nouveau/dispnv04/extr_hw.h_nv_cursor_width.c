#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ family; } ;
struct TYPE_5__ {TYPE_1__ info; } ;
struct TYPE_6__ {TYPE_2__ device; } ;
struct nouveau_drm {TYPE_3__ client; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int NV04_CURSOR_SIZE ; 
 int NV10_CURSOR_SIZE ; 
 scalar_t__ NV_DEVICE_INFO_V0_CELSIUS ; 
 struct nouveau_drm* nouveau_drm (struct drm_device*) ; 

__attribute__((used)) static inline int nv_cursor_width(struct drm_device *dev)
{
	struct nouveau_drm *drm = nouveau_drm(dev);

	return drm->client.device.info.family >= NV_DEVICE_INFO_V0_CELSIUS ? NV10_CURSOR_SIZE : NV04_CURSOR_SIZE;
}