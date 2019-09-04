#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u8 ;
typedef  scalar_t__ u32 ;
typedef  scalar_t__ u16 ;
struct nvkm_subdev {struct nvkm_device* device; } ;
struct nvkm_devinit {struct nvkm_subdev subdev; } ;
struct nvkm_device {struct nvkm_bios* bios; } ;
struct nvkm_bios {int dummy; } ;
struct io_mapping {int dummy; } ;

/* Variables and functions */
 int NV04_PFB_BOOT_0 ; 
 int NV04_PFB_BOOT_0_RAM_AMOUNT ; 
 int NV04_PFB_BOOT_0_RAM_AMOUNT_16MB ; 
 int NV04_PFB_BOOT_0_RAM_AMOUNT_32MB ; 
 int NV04_PFB_BOOT_0_RAM_AMOUNT_4MB ; 
 int NV04_PFB_BOOT_0_RAM_AMOUNT_8MB ; 
 int NV04_PFB_BOOT_0_RAM_WIDTH_128 ; 
 int NV04_PFB_BOOT_0_UMA_ENABLE ; 
 int NV04_PFB_CFG0 ; 
 int NV04_PFB_CFG0_SCRAMBLE ; 
 int NV04_PFB_CFG1 ; 
 int NV04_PFB_DEBUG_0 ; 
 int NV04_PFB_DEBUG_0_REFRESH_OFF ; 
 int /*<<< orphan*/  NV04_PFB_SCRAMBLE (int) ; 
 scalar_t__ bmp_mem_init_table (struct nvkm_bios*) ; 
 int /*<<< orphan*/  fbmem_fini (struct io_mapping*) ; 
 struct io_mapping* fbmem_init (struct nvkm_device*) ; 
 scalar_t__ fbmem_peek (struct io_mapping*,int) ; 
 int /*<<< orphan*/  fbmem_poke (struct io_mapping*,int,scalar_t__) ; 
 int /*<<< orphan*/  fbmem_readback (struct io_mapping*,int,scalar_t__) ; 
 int nvbios_rd08 (struct nvkm_bios*,scalar_t__) ; 
 scalar_t__ nvbios_rd32 (struct nvkm_bios*,scalar_t__) ; 
 int /*<<< orphan*/  nvkm_error (struct nvkm_subdev*,char*) ; 
 int /*<<< orphan*/  nvkm_mask (struct nvkm_device*,int,int,int) ; 
 int nvkm_rd32 (struct nvkm_device*,int) ; 
 int nvkm_rdvgas (struct nvkm_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nvkm_wr32 (struct nvkm_device*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  nvkm_wrvgas (struct nvkm_device*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void
nv05_devinit_meminit(struct nvkm_devinit *init)
{
	static const u8 default_config_tab[][2] = {
		{ 0x24, 0x00 },
		{ 0x28, 0x00 },
		{ 0x24, 0x01 },
		{ 0x1f, 0x00 },
		{ 0x0f, 0x00 },
		{ 0x17, 0x00 },
		{ 0x06, 0x00 },
		{ 0x00, 0x00 }
	};
	struct nvkm_subdev *subdev = &init->subdev;
	struct nvkm_device *device = subdev->device;
	struct nvkm_bios *bios = device->bios;
	struct io_mapping *fb;
	u32 patt = 0xdeadbeef;
	u16 data;
	u8 strap, ramcfg[2];
	int i, v;

	/* Map the framebuffer aperture */
	fb = fbmem_init(device);
	if (!fb) {
		nvkm_error(subdev, "failed to map fb\n");
		return;
	}

	strap = (nvkm_rd32(device, 0x101000) & 0x0000003c) >> 2;
	if ((data = bmp_mem_init_table(bios))) {
		ramcfg[0] = nvbios_rd08(bios, data + 2 * strap + 0);
		ramcfg[1] = nvbios_rd08(bios, data + 2 * strap + 1);
	} else {
		ramcfg[0] = default_config_tab[strap][0];
		ramcfg[1] = default_config_tab[strap][1];
	}

	/* Sequencer off */
	nvkm_wrvgas(device, 0, 1, nvkm_rdvgas(device, 0, 1) | 0x20);

	if (nvkm_rd32(device, NV04_PFB_BOOT_0) & NV04_PFB_BOOT_0_UMA_ENABLE)
		goto out;

	nvkm_mask(device, NV04_PFB_DEBUG_0, NV04_PFB_DEBUG_0_REFRESH_OFF, 0);

	/* If present load the hardcoded scrambling table */
	if (data) {
		for (i = 0, data += 0x10; i < 8; i++, data += 4) {
			u32 scramble = nvbios_rd32(bios, data);
			nvkm_wr32(device, NV04_PFB_SCRAMBLE(i), scramble);
		}
	}

	/* Set memory type/width/length defaults depending on the straps */
	nvkm_mask(device, NV04_PFB_BOOT_0, 0x3f, ramcfg[0]);

	if (ramcfg[1] & 0x80)
		nvkm_mask(device, NV04_PFB_CFG0, 0, NV04_PFB_CFG0_SCRAMBLE);

	nvkm_mask(device, NV04_PFB_CFG1, 0x700001, (ramcfg[1] & 1) << 20);
	nvkm_mask(device, NV04_PFB_CFG1, 0, 1);

	/* Probe memory bus width */
	for (i = 0; i < 4; i++)
		fbmem_poke(fb, 4 * i, patt);

	if (fbmem_peek(fb, 0xc) != patt)
		nvkm_mask(device, NV04_PFB_BOOT_0,
			  NV04_PFB_BOOT_0_RAM_WIDTH_128, 0);

	/* Probe memory length */
	v = nvkm_rd32(device, NV04_PFB_BOOT_0) & NV04_PFB_BOOT_0_RAM_AMOUNT;

	if (v == NV04_PFB_BOOT_0_RAM_AMOUNT_32MB &&
	    (!fbmem_readback(fb, 0x1000000, ++patt) ||
	     !fbmem_readback(fb, 0, ++patt)))
		nvkm_mask(device, NV04_PFB_BOOT_0, NV04_PFB_BOOT_0_RAM_AMOUNT,
			  NV04_PFB_BOOT_0_RAM_AMOUNT_16MB);

	if (v == NV04_PFB_BOOT_0_RAM_AMOUNT_16MB &&
	    !fbmem_readback(fb, 0x800000, ++patt))
		nvkm_mask(device, NV04_PFB_BOOT_0, NV04_PFB_BOOT_0_RAM_AMOUNT,
			  NV04_PFB_BOOT_0_RAM_AMOUNT_8MB);

	if (!fbmem_readback(fb, 0x400000, ++patt))
		nvkm_mask(device, NV04_PFB_BOOT_0, NV04_PFB_BOOT_0_RAM_AMOUNT,
			  NV04_PFB_BOOT_0_RAM_AMOUNT_4MB);

out:
	/* Sequencer on */
	nvkm_wrvgas(device, 0, 1, nvkm_rdvgas(device, 0, 1) & ~0x20);
	fbmem_fini(fb);
}