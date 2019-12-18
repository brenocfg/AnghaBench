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
struct nvkm_device {int dummy; } ;

/* Variables and functions */
 int nv04_gr_mthd_bind_class (struct nvkm_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nv04_gr_set_ctx_val (struct nvkm_device*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static bool
nv04_gr_mthd_bind_surf_src(struct nvkm_device *device, u32 inst, u32 data)
{
	switch (nv04_gr_mthd_bind_class(device, data)) {
	case 0x30:
		nv04_gr_set_ctx_val(device, inst, 0x04000000, 0);
		return true;
	case 0x59:
		nv04_gr_set_ctx_val(device, inst, 0x04000000, 0x04000000);
		return true;
	}
	return false;
}