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
typedef  int u64 ;
typedef  int u32 ;
struct nvkm_ram {int size; } ;
struct TYPE_2__ {struct nvkm_device* device; } ;
struct nvkm_ltc {int num_tags; int ltc_nr; int tag_base; int /*<<< orphan*/  tag_ram; TYPE_1__ subdev; } ;
struct nvkm_fb {int /*<<< orphan*/  tags; struct nvkm_ram* ram; } ;
struct nvkm_device {struct nvkm_fb* fb; } ;

/* Variables and functions */
 int /*<<< orphan*/  NVKM_RAM_MM_NORMAL ; 
 int /*<<< orphan*/  do_div (int,int) ; 
 int nvkm_memory_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvkm_mm_fini (int /*<<< orphan*/ *) ; 
 int nvkm_mm_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int nvkm_ram_get (struct nvkm_device*,int /*<<< orphan*/ ,int,int,int,int,int,int /*<<< orphan*/ *) ; 
 int nvkm_rd32 (struct nvkm_device*,int) ; 

int
gf100_ltc_oneinit_tag_ram(struct nvkm_ltc *ltc)
{
	struct nvkm_device *device = ltc->subdev.device;
	struct nvkm_fb *fb = device->fb;
	struct nvkm_ram *ram = fb->ram;
	u32 bits = (nvkm_rd32(device, 0x100c80) & 0x00001000) ? 16 : 17;
	u32 tag_size, tag_margin, tag_align;
	int ret;

	/* No VRAM, no tags for now. */
	if (!ram) {
		ltc->num_tags = 0;
		goto mm_init;
	}

	/* tags for 1/4 of VRAM should be enough (8192/4 per GiB of VRAM) */
	ltc->num_tags = (ram->size >> 17) / 4;
	if (ltc->num_tags > (1 << bits))
		ltc->num_tags = 1 << bits; /* we have 16/17 bits in PTE */
	ltc->num_tags = (ltc->num_tags + 63) & ~63; /* round up to 64 */

	tag_align = ltc->ltc_nr * 0x800;
	tag_margin = (tag_align < 0x6000) ? 0x6000 : tag_align;

	/* 4 part 4 sub: 0x2000 bytes for 56 tags */
	/* 3 part 4 sub: 0x6000 bytes for 168 tags */
	/*
	 * About 147 bytes per tag. Let's be safe and allocate x2, which makes
	 * 0x4980 bytes for 64 tags, and round up to 0x6000 bytes for 64 tags.
	 *
	 * For 4 GiB of memory we'll have 8192 tags which makes 3 MiB, < 0.1 %.
	 */
	tag_size  = (ltc->num_tags / 64) * 0x6000 + tag_margin;
	tag_size += tag_align;

	ret = nvkm_ram_get(device, NVKM_RAM_MM_NORMAL, 0x01, 12, tag_size,
			   true, true, &ltc->tag_ram);
	if (ret) {
		ltc->num_tags = 0;
	} else {
		u64 tag_base = nvkm_memory_addr(ltc->tag_ram) + tag_margin;

		tag_base += tag_align - 1;
		do_div(tag_base, tag_align);

		ltc->tag_base = tag_base;
	}

mm_init:
	nvkm_mm_fini(&fb->tags);
	return nvkm_mm_init(&fb->tags, 0, 0, ltc->num_tags, 1);
}