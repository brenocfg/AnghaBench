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
struct nvkm_gr {int dummy; } ;
struct nvkm_device {int dummy; } ;
struct gf100_gr_func {int dummy; } ;
struct gf100_gr {int /*<<< orphan*/  fuc41ad; int /*<<< orphan*/  fuc41ac; int /*<<< orphan*/  fuc409d; int /*<<< orphan*/  fuc409c; scalar_t__ firmware; struct nvkm_gr base; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int gf100_gr_ctor (struct gf100_gr_func const*,struct nvkm_device*,int,struct gf100_gr*) ; 
 scalar_t__ gf100_gr_ctor_fw (struct gf100_gr*,char*,int /*<<< orphan*/ *) ; 
 struct gf100_gr* kzalloc (int,int /*<<< orphan*/ ) ; 

int
gf100_gr_new_(const struct gf100_gr_func *func, struct nvkm_device *device,
	      int index, struct nvkm_gr **pgr)
{
	struct gf100_gr *gr;
	int ret;

	if (!(gr = kzalloc(sizeof(*gr), GFP_KERNEL)))
		return -ENOMEM;
	*pgr = &gr->base;

	ret = gf100_gr_ctor(func, device, index, gr);
	if (ret)
		return ret;

	if (gr->firmware) {
		if (gf100_gr_ctor_fw(gr, "fecs_inst", &gr->fuc409c) ||
		    gf100_gr_ctor_fw(gr, "fecs_data", &gr->fuc409d) ||
		    gf100_gr_ctor_fw(gr, "gpccs_inst", &gr->fuc41ac) ||
		    gf100_gr_ctor_fw(gr, "gpccs_data", &gr->fuc41ad))
			return -ENODEV;
	}

	return 0;
}