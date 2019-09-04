#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {struct nvkm_device* device; } ;
struct nvkm_gpio {TYPE_1__ subdev; } ;
struct nvkm_device {struct nvkm_bios* bios; } ;
struct nvkm_bios {int dummy; } ;

/* Variables and functions */
 scalar_t__ DCB_GPIO_UNUSED ; 
 int /*<<< orphan*/  dcb_gpio_entry (struct nvkm_bios*,int /*<<< orphan*/ ,int,scalar_t__*,scalar_t__*) ; 
 int nvbios_rd32 (struct nvkm_bios*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvkm_gpio_set (struct nvkm_gpio*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  nvkm_mask (struct nvkm_device*,int,int,scalar_t__) ; 

void
gf119_gpio_reset(struct nvkm_gpio *gpio, u8 match)
{
	struct nvkm_device *device = gpio->subdev.device;
	struct nvkm_bios *bios = device->bios;
	u8 ver, len;
	u16 entry;
	int ent = -1;

	while ((entry = dcb_gpio_entry(bios, 0, ++ent, &ver, &len))) {
		u32 data = nvbios_rd32(bios, entry);
		u8  line =   (data & 0x0000003f);
		u8  defs = !!(data & 0x00000080);
		u8  func =   (data & 0x0000ff00) >> 8;
		u8  unk0 =   (data & 0x00ff0000) >> 16;
		u8  unk1 =   (data & 0x1f000000) >> 24;

		if ( func  == DCB_GPIO_UNUSED ||
		    (match != DCB_GPIO_UNUSED && match != func))
			continue;

		nvkm_gpio_set(gpio, 0, func, line, defs);

		nvkm_mask(device, 0x00d610 + (line * 4), 0xff, unk0);
		if (unk1--)
			nvkm_mask(device, 0x00d740 + (unk1 * 4), 0xff, line);
	}
}