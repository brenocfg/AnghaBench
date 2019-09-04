#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct nvif_device {int /*<<< orphan*/  object; } ;
struct drm_device {int dummy; } ;
struct TYPE_3__ {struct nvif_device device; } ;
struct TYPE_4__ {TYPE_1__ client; } ;

/* Variables and functions */
 TYPE_2__* nouveau_drm (struct drm_device*) ; 
 int /*<<< orphan*/  nvif_wr32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void nv_write_ptv(struct drm_device *dev, uint32_t reg,
				uint32_t val)
{
	struct nvif_device *device = &nouveau_drm(dev)->client.device;
	nvif_wr32(&device->object, reg, val);
}