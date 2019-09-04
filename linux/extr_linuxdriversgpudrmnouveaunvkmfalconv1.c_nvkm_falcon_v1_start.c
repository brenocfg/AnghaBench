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
struct nvkm_falcon {int dummy; } ;

/* Variables and functions */
 int BIT (int) ; 
 int nvkm_falcon_rd32 (struct nvkm_falcon*,int) ; 
 int /*<<< orphan*/  nvkm_falcon_wr32 (struct nvkm_falcon*,int,int) ; 

__attribute__((used)) static void
nvkm_falcon_v1_start(struct nvkm_falcon *falcon)
{
	u32 reg = nvkm_falcon_rd32(falcon, 0x100);

	if (reg & BIT(6))
		nvkm_falcon_wr32(falcon, 0x130, 0x2);
	else
		nvkm_falcon_wr32(falcon, 0x100, 0x2);
}