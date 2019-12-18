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
typedef  int u64 ;
typedef  int u32 ;
struct nvkm_subdev {struct nvkm_device* device; } ;
struct nvkm_ram_func {int (* probe_fbp ) (struct nvkm_ram_func const*,struct nvkm_device*,int,int*) ;int upper; } ;
struct nvkm_ram {int /*<<< orphan*/  vram; } ;
struct nvkm_fb {struct nvkm_subdev subdev; } ;
struct nvkm_device {struct nvkm_bios* bios; } ;
struct nvkm_bios {int dummy; } ;
typedef  enum nvkm_ram_type { ____Placeholder_nvkm_ram_type } nvkm_ram_type ;

/* Variables and functions */
 int /*<<< orphan*/  NVKM_RAM_MM_MIXED ; 
 int /*<<< orphan*/  NVKM_RAM_MM_NORMAL ; 
 int const NVKM_RAM_MM_SHIFT ; 
 int min (int,int) ; 
 int /*<<< orphan*/  nvkm_debug (struct nvkm_subdev*,char*,int,...) ; 
 int nvkm_fb_bios_memtype (struct nvkm_bios*) ; 
 int /*<<< orphan*/  nvkm_mm_fini (int /*<<< orphan*/ *) ; 
 int nvkm_mm_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int const,int,int) ; 
 int nvkm_ram_ctor (struct nvkm_ram_func const*,struct nvkm_fb*,int,int,struct nvkm_ram*) ; 
 int nvkm_rd32 (struct nvkm_device*,int) ; 
 int stub1 (struct nvkm_ram_func const*,struct nvkm_device*,int,int*) ; 

int
gf100_ram_ctor(const struct nvkm_ram_func *func, struct nvkm_fb *fb,
	       struct nvkm_ram *ram)
{
	struct nvkm_subdev *subdev = &fb->subdev;
	struct nvkm_device *device = subdev->device;
	struct nvkm_bios *bios = device->bios;
	const u32 rsvd_head = ( 256 * 1024); /* vga memory */
	const u32 rsvd_tail = (1024 * 1024); /* vbios etc */
	enum nvkm_ram_type type = nvkm_fb_bios_memtype(bios);
	u32 fbps = nvkm_rd32(device, 0x022438);
	u64 total = 0, lcomm = ~0, lower, ubase, usize;
	int ret, fbp, ltcs, ltcn = 0;

	nvkm_debug(subdev, "%d FBP(s)\n", fbps);
	for (fbp = 0; fbp < fbps; fbp++) {
		u32 size = func->probe_fbp(func, device, fbp, &ltcs);
		if (size) {
			nvkm_debug(subdev, "FBP %d: %4d MiB, %d LTC(s)\n",
				   fbp, size, ltcs);
			lcomm  = min(lcomm, (u64)(size / ltcs) << 20);
			total += (u64) size << 20;
			ltcn  += ltcs;
		} else {
			nvkm_debug(subdev, "FBP %d: disabled\n", fbp);
		}
	}

	lower = lcomm * ltcn;
	ubase = lcomm + func->upper;
	usize = total - lower;

	nvkm_debug(subdev, "Lower: %4lld MiB @ %010llx\n", lower >> 20, 0ULL);
	nvkm_debug(subdev, "Upper: %4lld MiB @ %010llx\n", usize >> 20, ubase);
	nvkm_debug(subdev, "Total: %4lld MiB\n", total >> 20);

	ret = nvkm_ram_ctor(func, fb, type, total, ram);
	if (ret)
		return ret;

	nvkm_mm_fini(&ram->vram);

	/* Some GPUs are in what's known as a "mixed memory" configuration.
	 *
	 * This is either where some FBPs have more memory than the others,
	 * or where LTCs have been disabled on a FBP.
	 */
	if (lower != total) {
		/* The common memory amount is addressed normally. */
		ret = nvkm_mm_init(&ram->vram, NVKM_RAM_MM_NORMAL,
				   rsvd_head >> NVKM_RAM_MM_SHIFT,
				   (lower - rsvd_head) >> NVKM_RAM_MM_SHIFT, 1);
		if (ret)
			return ret;

		/* And the rest is much higher in the physical address
		 * space, and may not be usable for certain operations.
		 */
		ret = nvkm_mm_init(&ram->vram, NVKM_RAM_MM_MIXED,
				   ubase >> NVKM_RAM_MM_SHIFT,
				   (usize - rsvd_tail) >> NVKM_RAM_MM_SHIFT, 1);
		if (ret)
			return ret;
	} else {
		/* GPUs without mixed-memory are a lot nicer... */
		ret = nvkm_mm_init(&ram->vram, NVKM_RAM_MM_NORMAL,
				   rsvd_head >> NVKM_RAM_MM_SHIFT,
				   (total - rsvd_head - rsvd_tail) >>
				   NVKM_RAM_MM_SHIFT, 1);
		if (ret)
			return ret;
	}

	return 0;
}