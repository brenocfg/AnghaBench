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
struct TYPE_3__ {scalar_t__ family; int chipset; } ;
struct nvif_device {TYPE_1__ info; } ;
struct TYPE_4__ {struct nvif_device device; } ;
struct nouveau_drm {int /*<<< orphan*/  cechan; TYPE_2__ client; } ;

/* Variables and functions */
 scalar_t__ NV_DEVICE_INFO_V0_KEPLER ; 
 int /*<<< orphan*/  NV_ERROR (struct nouveau_drm*,char*,int) ; 
 int /*<<< orphan*/  NvDmaFB ; 
 int /*<<< orphan*/  NvDmaTT ; 
 int nouveau_channel_new (struct nouveau_drm*,struct nvif_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvif_fifo_runlist_ce (struct nvif_device*) ; 

__attribute__((used)) static void
nouveau_accel_ce_init(struct nouveau_drm *drm)
{
	struct nvif_device *device = &drm->client.device;
	int ret = 0;

	/* Allocate channel that has access to a (preferably async) copy
	 * engine, to use for TTM buffer moves.
	 */
	if (device->info.family >= NV_DEVICE_INFO_V0_KEPLER) {
		ret = nouveau_channel_new(drm, device,
					  nvif_fifo_runlist_ce(device), 0,
					  true, &drm->cechan);
	} else
	if (device->info.chipset >= 0xa3 &&
	    device->info.chipset != 0xaa &&
	    device->info.chipset != 0xac) {
		/* Prior to Kepler, there's only a single runlist, so all
		 * engines can be accessed from any channel.
		 *
		 * We still want to use a separate channel though.
		 */
		ret = nouveau_channel_new(drm, device, NvDmaFB, NvDmaTT, false,
					  &drm->cechan);
	}

	if (ret)
		NV_ERROR(drm, "failed to create ce channel, %d\n", ret);
}