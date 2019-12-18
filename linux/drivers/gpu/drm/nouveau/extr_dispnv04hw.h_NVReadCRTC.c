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
typedef  int /*<<< orphan*/  uint32_t ;
struct nvif_object {int dummy; } ;
struct drm_device {int dummy; } ;
struct TYPE_4__ {struct nvif_object object; } ;
struct TYPE_5__ {TYPE_1__ device; } ;
struct TYPE_6__ {TYPE_2__ client; } ;

/* Variables and functions */
 scalar_t__ NV_PCRTC0_SIZE ; 
 TYPE_3__* nouveau_drm (struct drm_device*) ; 
 int /*<<< orphan*/  nvif_rd32 (struct nvif_object*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline uint32_t NVReadCRTC(struct drm_device *dev,
					int head, uint32_t reg)
{
	struct nvif_object *device = &nouveau_drm(dev)->client.device.object;
	uint32_t val;
	if (head)
		reg += NV_PCRTC0_SIZE;
	val = nvif_rd32(device, reg);
	return val;
}