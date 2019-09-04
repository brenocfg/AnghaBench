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
typedef  int u32 ;
struct nvkm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nv04_gr_set_ctx1 (struct nvkm_device*,int,int,int) ; 
 int /*<<< orphan*/  nv04_gr_set_ctx_val (struct nvkm_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nvkm_rd32 (struct nvkm_device*,int) ; 

__attribute__((used)) static bool
nv04_gr_mthd_set_operation(struct nvkm_device *device, u32 inst, u32 data)
{
	u8 class = nvkm_rd32(device, 0x700000) & 0x000000ff;
	if (data > 5)
		return false;
	/* Old versions of the objects only accept first three operations. */
	if (data > 2 && class < 0x40)
		return false;
	nv04_gr_set_ctx1(device, inst, 0x00038000, data << 15);
	/* changing operation changes set of objects needed for validation */
	nv04_gr_set_ctx_val(device, inst, 0, 0);
	return true;
}