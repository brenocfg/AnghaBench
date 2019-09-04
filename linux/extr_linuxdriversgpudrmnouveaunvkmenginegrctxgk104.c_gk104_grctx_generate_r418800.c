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
struct nvkm_device {int dummy; } ;
struct TYPE_4__ {struct nvkm_device* device; } ;
struct TYPE_5__ {TYPE_1__ subdev; } ;
struct TYPE_6__ {TYPE_2__ engine; } ;
struct gf100_gr {TYPE_3__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvkm_mask (struct nvkm_device*,int,int,int) ; 

void
gk104_grctx_generate_r418800(struct gf100_gr *gr)
{
	struct nvkm_device *device = gr->base.engine.subdev.device;
	/*XXX: Not real sure where to apply these, there doesn't seem
	 *     to be any pattern to which chipsets it's done on.
	 *
	 *     Perhaps a VBIOS tweak?
	 */
	if (0) {
		nvkm_mask(device, 0x418800, 0x00200000, 0x00200000);
		nvkm_mask(device, 0x41be10, 0x00800000, 0x00800000);
	}
}