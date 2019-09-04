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
typedef  int u32 ;
struct nvkm_object {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  FERMI_A_ZBC_COLOR 129 
#define  FERMI_A_ZBC_DEPTH 128 
 int gf100_fermi_mthd_zbc_color (struct nvkm_object*,void*,int) ; 
 int gf100_fermi_mthd_zbc_depth (struct nvkm_object*,void*,int) ; 
 int /*<<< orphan*/  nvif_ioctl (struct nvkm_object*,char*,int) ; 

__attribute__((used)) static int
gf100_fermi_mthd(struct nvkm_object *object, u32 mthd, void *data, u32 size)
{
	nvif_ioctl(object, "fermi mthd %08x\n", mthd);
	switch (mthd) {
	case FERMI_A_ZBC_COLOR:
		return gf100_fermi_mthd_zbc_color(object, data, size);
	case FERMI_A_ZBC_DEPTH:
		return gf100_fermi_mthd_zbc_depth(object, data, size);
	default:
		break;
	}
	return -EINVAL;
}