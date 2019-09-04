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
typedef  int u16 ;
struct nvkm_device {int dummy; } ;

/* Variables and functions */
 int nvkm_rdvgac (struct nvkm_device*,int,int) ; 
 int nvkm_rdvgag (struct nvkm_device*,int,int) ; 
 int nvkm_rdvgas (struct nvkm_device*,int,int) ; 

u8
nvkm_rdvgai(struct nvkm_device *device, int head, u16 port, u8 index)
{
	if (port == 0x03c4) return nvkm_rdvgas(device, head, index);
	if (port == 0x03ce) return nvkm_rdvgag(device, head, index);
	if (port == 0x03d4) return nvkm_rdvgac(device, head, index);
	return 0x00;
}