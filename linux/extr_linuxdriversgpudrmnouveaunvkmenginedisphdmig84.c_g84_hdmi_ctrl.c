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
typedef  int u8 ;
typedef  int u32 ;
struct packed_hdmi_infoframe {int header; int subpack0_low; int subpack0_high; int subpack1_low; int subpack1_high; } ;
struct nvkm_ior {TYPE_3__* disp; } ;
struct nvkm_device {int dummy; } ;
struct TYPE_4__ {struct nvkm_device* device; } ;
struct TYPE_5__ {TYPE_1__ subdev; } ;
struct TYPE_6__ {TYPE_2__ engine; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvkm_mask (struct nvkm_device*,int,int,int const) ; 
 int /*<<< orphan*/  nvkm_wr32 (struct nvkm_device*,int,int) ; 
 int /*<<< orphan*/  pack_hdmi_infoframe (struct packed_hdmi_infoframe*,int*,int) ; 

void
g84_hdmi_ctrl(struct nvkm_ior *ior, int head, bool enable, u8 max_ac_packet,
	      u8 rekey, u8 *avi, u8 avi_size, u8 *vendor, u8 vendor_size)
{
	struct nvkm_device *device = ior->disp->engine.subdev.device;
	const u32 ctrl = 0x40000000 * enable |
			 0x1f000000 /* ??? */ |
			 max_ac_packet << 16 |
			 rekey;
	const u32 hoff = head * 0x800;
	struct packed_hdmi_infoframe avi_infoframe;
	struct packed_hdmi_infoframe vendor_infoframe;

	pack_hdmi_infoframe(&avi_infoframe, avi, avi_size);
	pack_hdmi_infoframe(&vendor_infoframe, vendor, vendor_size);

	if (!(ctrl & 0x40000000)) {
		nvkm_mask(device, 0x6165a4 + hoff, 0x40000000, 0x00000000);
		nvkm_mask(device, 0x61653c + hoff, 0x00000001, 0x00000000);
		nvkm_mask(device, 0x616520 + hoff, 0x00000001, 0x00000000);
		nvkm_mask(device, 0x616500 + hoff, 0x00000001, 0x00000000);
		return;
	}

	/* AVI InfoFrame */
	nvkm_mask(device, 0x616520 + hoff, 0x00000001, 0x00000000);
	if (avi_size) {
		nvkm_wr32(device, 0x616528 + hoff, avi_infoframe.header);
		nvkm_wr32(device, 0x61652c + hoff, avi_infoframe.subpack0_low);
		nvkm_wr32(device, 0x616530 + hoff, avi_infoframe.subpack0_high);
		nvkm_wr32(device, 0x616534 + hoff, avi_infoframe.subpack1_low);
		nvkm_wr32(device, 0x616538 + hoff, avi_infoframe.subpack1_high);
		nvkm_mask(device, 0x616520 + hoff, 0x00000001, 0x00000001);
	}

	/* Audio InfoFrame */
	nvkm_mask(device, 0x616500 + hoff, 0x00000001, 0x00000000);
	nvkm_wr32(device, 0x616508 + hoff, 0x000a0184);
	nvkm_wr32(device, 0x61650c + hoff, 0x00000071);
	nvkm_wr32(device, 0x616510 + hoff, 0x00000000);
	nvkm_mask(device, 0x616500 + hoff, 0x00000001, 0x00000001);

	/* Vendor InfoFrame */
	nvkm_mask(device, 0x61653c + hoff, 0x00010001, 0x00010000);
	if (vendor_size) {
		nvkm_wr32(device, 0x616544 + hoff, vendor_infoframe.header);
		nvkm_wr32(device, 0x616548 + hoff, vendor_infoframe.subpack0_low);
		nvkm_wr32(device, 0x61654c + hoff, vendor_infoframe.subpack0_high);
		/* Is there a second (or up to fourth?) set of subpack registers here? */
		/* nvkm_wr32(device, 0x616550 + hoff, vendor_infoframe->subpack1_low); */
		/* nvkm_wr32(device, 0x616554 + hoff, vendor_infoframe->subpack1_high); */
		nvkm_mask(device, 0x61653c + hoff, 0x00010001, 0x00010001);
	}

	nvkm_mask(device, 0x6165d0 + hoff, 0x00070001, 0x00010001); /* SPARE, HW_CTS */
	nvkm_mask(device, 0x616568 + hoff, 0x00010101, 0x00000000); /* ACR_CTRL, ?? */
	nvkm_mask(device, 0x616578 + hoff, 0x80000000, 0x80000000); /* ACR_0441_ENABLE */

	/* ??? */
	nvkm_mask(device, 0x61733c, 0x00100000, 0x00100000); /* RESETF */
	nvkm_mask(device, 0x61733c, 0x10000000, 0x10000000); /* LOOKUP_EN */
	nvkm_mask(device, 0x61733c, 0x00100000, 0x00000000); /* !RESETF */

	/* HDMI_CTRL */
	nvkm_mask(device, 0x6165a4 + hoff, 0x5f1f007f, ctrl);
}