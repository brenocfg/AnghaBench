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
typedef  unsigned long long u64 ;
struct nvkm_subdev {struct nvkm_device* device; } ;
struct nvkm_devinit {int post; struct nvkm_subdev subdev; } ;
struct nvkm_device {int dummy; } ;

/* Variables and functions */
 unsigned long long NVKM_ENGINE_DISP ; 
 int /*<<< orphan*/  nvkm_debug (struct nvkm_subdev*,char*) ; 
 unsigned long long nvkm_devinit_disable (struct nvkm_devinit*) ; 
 int /*<<< orphan*/  nvkm_rdvgac (struct nvkm_device*,int /*<<< orphan*/ ,int) ; 

void
nv50_devinit_preinit(struct nvkm_devinit *base)
{
	struct nvkm_subdev *subdev = &base->subdev;
	struct nvkm_device *device = subdev->device;

	/* our heuristics can't detect whether the board has had its
	 * devinit scripts executed or not if the display engine is
	 * missing, assume it's a secondary gpu which requires post
	 */
	if (!base->post) {
		u64 disable = nvkm_devinit_disable(base);
		if (disable & (1ULL << NVKM_ENGINE_DISP))
			base->post = true;
	}

	/* magic to detect whether or not x86 vbios code has executed
	 * the devinit scripts to initialise the board
	 */
	if (!base->post) {
		if (!nvkm_rdvgac(device, 0, 0x00) &&
		    !nvkm_rdvgac(device, 0, 0x1a)) {
			nvkm_debug(subdev, "adaptor not initialised\n");
			base->post = true;
		}
	}
}