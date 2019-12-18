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
struct nvkm_ram_func {scalar_t__ (* probe_fbpa_amount ) (struct nvkm_device*,int) ;} ;
struct nvkm_device {int dummy; } ;

/* Variables and functions */
 int BIT (int) ; 
 int nvkm_rd32 (struct nvkm_device*,int) ; 
 scalar_t__ stub1 (struct nvkm_device*,int) ; 

u32
gf108_ram_probe_fbp_amount(const struct nvkm_ram_func *func, u32 fbpao,
			   struct nvkm_device *device, int fbp, int *pltcs)
{
	u32 fbpt  = nvkm_rd32(device, 0x022438);
	u32 fbpat = nvkm_rd32(device, 0x02243c);
	u32 fbpas = fbpat / fbpt;
	u32 fbpa  = fbp * fbpas;
	u32 size  = 0;
	while (fbpas--) {
		if (!(fbpao & BIT(fbpa)))
			size += func->probe_fbpa_amount(device, fbpa);
		fbpa++;
	}
	*pltcs = 1;
	return size;
}