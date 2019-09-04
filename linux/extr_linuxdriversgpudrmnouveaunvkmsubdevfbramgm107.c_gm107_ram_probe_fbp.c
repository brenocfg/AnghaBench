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
struct nvkm_ram_func {int /*<<< orphan*/  (* probe_fbp_amount ) (struct nvkm_ram_func const*,int /*<<< orphan*/ ,struct nvkm_device*,int,int*) ;} ;
struct nvkm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvkm_rd32 (struct nvkm_device*,int) ; 
 int /*<<< orphan*/  stub1 (struct nvkm_ram_func const*,int /*<<< orphan*/ ,struct nvkm_device*,int,int*) ; 

u32
gm107_ram_probe_fbp(const struct nvkm_ram_func *func,
		    struct nvkm_device *device, int fbp, int *pltcs)
{
	u32 fbpao = nvkm_rd32(device, 0x021c14);
	return func->probe_fbp_amount(func, fbpao, device, fbp, pltcs);
}