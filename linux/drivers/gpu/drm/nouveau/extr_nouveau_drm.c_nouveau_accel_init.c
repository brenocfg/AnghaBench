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
struct nvif_sclass {int oclass; } ;
struct TYPE_3__ {scalar_t__ family; } ;
struct nvif_device {TYPE_1__ info; int /*<<< orphan*/  object; } ;
struct TYPE_4__ {struct nvif_device device; } ;
struct nouveau_drm {TYPE_2__ client; } ;

/* Variables and functions */
 int ENOSYS ; 
#define  FERMI_CHANNEL_GPFIFO 140 
#define  G82_CHANNEL_GPFIFO 139 
#define  KEPLER_CHANNEL_GPFIFO_A 138 
#define  KEPLER_CHANNEL_GPFIFO_B 137 
#define  MAXWELL_CHANNEL_GPFIFO_A 136 
#define  NV03_CHANNEL_DMA 135 
#define  NV10_CHANNEL_DMA 134 
#define  NV17_CHANNEL_DMA 133 
#define  NV40_CHANNEL_DMA 132 
#define  NV50_CHANNEL_GPFIFO 131 
 scalar_t__ NV_DEVICE_INFO_V0_VOLTA ; 
 int /*<<< orphan*/  NV_ERROR (struct nouveau_drm*,char*,int) ; 
#define  PASCAL_CHANNEL_GPFIFO_A 130 
#define  TURING_CHANNEL_GPFIFO_A 129 
#define  VOLTA_CHANNEL_GPFIFO_A 128 
 int /*<<< orphan*/  nouveau_accel_ce_init (struct nouveau_drm*) ; 
 int /*<<< orphan*/  nouveau_accel_fini (struct nouveau_drm*) ; 
 int /*<<< orphan*/  nouveau_accel_gr_init (struct nouveau_drm*) ; 
 int /*<<< orphan*/  nouveau_bo_move_init (struct nouveau_drm*) ; 
 int nouveau_channels_init (struct nouveau_drm*) ; 
 scalar_t__ nouveau_noaccel ; 
 int nv04_fence_create (struct nouveau_drm*) ; 
 int nv10_fence_create (struct nouveau_drm*) ; 
 int nv17_fence_create (struct nouveau_drm*) ; 
 int nv50_fence_create (struct nouveau_drm*) ; 
 int nv84_fence_create (struct nouveau_drm*) ; 
 int nvc0_fence_create (struct nouveau_drm*) ; 
 int nvif_object_sclass_get (int /*<<< orphan*/ *,struct nvif_sclass**) ; 
 int /*<<< orphan*/  nvif_object_sclass_put (struct nvif_sclass**) ; 
 int nvif_user_init (struct nvif_device*) ; 

__attribute__((used)) static void
nouveau_accel_init(struct nouveau_drm *drm)
{
	struct nvif_device *device = &drm->client.device;
	struct nvif_sclass *sclass;
	int ret, i, n;

	if (nouveau_noaccel)
		return;

	/* Initialise global support for channels, and synchronisation. */
	ret = nouveau_channels_init(drm);
	if (ret)
		return;

	/*XXX: this is crap, but the fence/channel stuff is a little
	 *     backwards in some places.  this will be fixed.
	 */
	ret = n = nvif_object_sclass_get(&device->object, &sclass);
	if (ret < 0)
		return;

	for (ret = -ENOSYS, i = 0; i < n; i++) {
		switch (sclass[i].oclass) {
		case NV03_CHANNEL_DMA:
			ret = nv04_fence_create(drm);
			break;
		case NV10_CHANNEL_DMA:
			ret = nv10_fence_create(drm);
			break;
		case NV17_CHANNEL_DMA:
		case NV40_CHANNEL_DMA:
			ret = nv17_fence_create(drm);
			break;
		case NV50_CHANNEL_GPFIFO:
			ret = nv50_fence_create(drm);
			break;
		case G82_CHANNEL_GPFIFO:
			ret = nv84_fence_create(drm);
			break;
		case FERMI_CHANNEL_GPFIFO:
		case KEPLER_CHANNEL_GPFIFO_A:
		case KEPLER_CHANNEL_GPFIFO_B:
		case MAXWELL_CHANNEL_GPFIFO_A:
		case PASCAL_CHANNEL_GPFIFO_A:
		case VOLTA_CHANNEL_GPFIFO_A:
		case TURING_CHANNEL_GPFIFO_A:
			ret = nvc0_fence_create(drm);
			break;
		default:
			break;
		}
	}

	nvif_object_sclass_put(&sclass);
	if (ret) {
		NV_ERROR(drm, "failed to initialise sync subsystem, %d\n", ret);
		nouveau_accel_fini(drm);
		return;
	}

	/* Volta requires access to a doorbell register for kickoff. */
	if (drm->client.device.info.family >= NV_DEVICE_INFO_V0_VOLTA) {
		ret = nvif_user_init(device);
		if (ret)
			return;
	}

	/* Allocate channels we need to support various functions. */
	nouveau_accel_gr_init(drm);
	nouveau_accel_ce_init(drm);

	/* Initialise accelerated TTM buffer moves. */
	nouveau_bo_move_init(drm);
}