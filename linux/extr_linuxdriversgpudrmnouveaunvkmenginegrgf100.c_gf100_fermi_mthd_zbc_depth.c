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
typedef  int /*<<< orphan*/  u32 ;
struct nvkm_object {int /*<<< orphan*/  engine; } ;
struct gf100_gr {int dummy; } ;
struct fermi_a_zbc_depth_v0 {int format; int /*<<< orphan*/  l2; int /*<<< orphan*/  ds; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOSPC ; 
 int ENOSYS ; 
#define  FERMI_A_ZBC_DEPTH_V0_FMT_FP32 128 
 struct gf100_gr* gf100_gr (int /*<<< orphan*/ ) ; 
 int gf100_gr_zbc_depth_get (struct gf100_gr*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nvif_unpack (int,void**,int /*<<< orphan*/ *,struct fermi_a_zbc_depth_v0,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nvkm_gr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
gf100_fermi_mthd_zbc_depth(struct nvkm_object *object, void *data, u32 size)
{
	struct gf100_gr *gr = gf100_gr(nvkm_gr(object->engine));
	union {
		struct fermi_a_zbc_depth_v0 v0;
	} *args = data;
	int ret = -ENOSYS;

	if (!(ret = nvif_unpack(ret, &data, &size, args->v0, 0, 0, false))) {
		switch (args->v0.format) {
		case FERMI_A_ZBC_DEPTH_V0_FMT_FP32:
			ret = gf100_gr_zbc_depth_get(gr, args->v0.format,
							   args->v0.ds,
							   args->v0.l2);
			return (ret >= 0) ? 0 : -ENOSPC;
		default:
			return -EINVAL;
		}
	}

	return ret;
}