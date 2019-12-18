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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct nvif_object {int dummy; } ;
struct TYPE_4__ {scalar_t__ family; } ;
struct TYPE_5__ {TYPE_1__ info; struct nvif_object object; } ;
struct TYPE_6__ {TYPE_2__ device; } ;
struct nouveau_drm {TYPE_3__ client; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ NV_DEVICE_INFO_V0_CURIE ; 
 scalar_t__ NV_PRMVIO_SIZE ; 
 struct nouveau_drm* nouveau_drm (struct drm_device*) ; 
 int /*<<< orphan*/  nvif_rd08 (struct nvif_object*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline uint8_t NVReadPRMVIO(struct drm_device *dev,
					int head, uint32_t reg)
{
	struct nvif_object *device = &nouveau_drm(dev)->client.device.object;
	struct nouveau_drm *drm = nouveau_drm(dev);
	uint8_t val;

	/* Only NV4x have two pvio ranges; other twoHeads cards MUST call
	 * NVSetOwner for the relevant head to be programmed */
	if (head && drm->client.device.info.family == NV_DEVICE_INFO_V0_CURIE)
		reg += NV_PRMVIO_SIZE;

	val = nvif_rd08(device, reg);
	return val;
}