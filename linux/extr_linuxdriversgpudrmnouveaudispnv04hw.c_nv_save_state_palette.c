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
struct nvif_object {int dummy; } ;
struct nv04_mode_state {TYPE_1__* crtc_reg; } ;
struct drm_device {int dummy; } ;
struct TYPE_6__ {struct nvif_object object; } ;
struct TYPE_7__ {TYPE_2__ device; } ;
struct TYPE_8__ {TYPE_3__ client; } ;
struct TYPE_5__ {int /*<<< orphan*/ * DAC; } ;

/* Variables and functions */
 int /*<<< orphan*/  NVSetEnablePalette (struct drm_device*,int,int) ; 
 scalar_t__ NV_PRMDIO_PALETTE_DATA ; 
 scalar_t__ NV_PRMDIO_PIXEL_MASK ; 
 int NV_PRMDIO_PIXEL_MASK_MASK ; 
 scalar_t__ NV_PRMDIO_READ_MODE_ADDRESS ; 
 int NV_PRMDIO_SIZE ; 
 TYPE_4__* nouveau_drm (struct drm_device*) ; 
 int /*<<< orphan*/  nvif_rd08 (struct nvif_object*,scalar_t__) ; 
 int /*<<< orphan*/  nvif_wr08 (struct nvif_object*,scalar_t__,int) ; 

__attribute__((used)) static void
nv_save_state_palette(struct drm_device *dev, int head,
		      struct nv04_mode_state *state)
{
	struct nvif_object *device = &nouveau_drm(dev)->client.device.object;
	int head_offset = head * NV_PRMDIO_SIZE, i;

	nvif_wr08(device, NV_PRMDIO_PIXEL_MASK + head_offset,
				NV_PRMDIO_PIXEL_MASK_MASK);
	nvif_wr08(device, NV_PRMDIO_READ_MODE_ADDRESS + head_offset, 0x0);

	for (i = 0; i < 768; i++) {
		state->crtc_reg[head].DAC[i] = nvif_rd08(device,
				NV_PRMDIO_PALETTE_DATA + head_offset);
	}

	NVSetEnablePalette(dev, head, false);
}