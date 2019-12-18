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
struct gf100_gr_fuc {int /*<<< orphan*/ * data; int /*<<< orphan*/  size; } ;
struct TYPE_3__ {int /*<<< orphan*/  subdev; } ;
struct TYPE_4__ {TYPE_1__ engine; } ;
struct gf100_gr {TYPE_2__ base; } ;
struct firmware {int /*<<< orphan*/  data; int /*<<< orphan*/  size; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int gf100_gr_ctor_fw_legacy (struct gf100_gr*,char const*,struct gf100_gr_fuc*,int) ; 
 int /*<<< orphan*/ * kmemdup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nvkm_firmware_get (int /*<<< orphan*/ *,char const*,struct firmware const**) ; 
 int /*<<< orphan*/  nvkm_firmware_put (struct firmware const*) ; 

int
gf100_gr_ctor_fw(struct gf100_gr *gr, const char *fwname,
		 struct gf100_gr_fuc *fuc)
{
	const struct firmware *fw;
	int ret;

	ret = nvkm_firmware_get(&gr->base.engine.subdev, fwname, &fw);
	if (ret) {
		ret = gf100_gr_ctor_fw_legacy(gr, fwname, fuc, ret);
		if (ret)
			return -ENODEV;
		return 0;
	}

	fuc->size = fw->size;
	fuc->data = kmemdup(fw->data, fuc->size, GFP_KERNEL);
	nvkm_firmware_put(fw);
	return (fuc->data != NULL) ? 0 : -ENOMEM;
}