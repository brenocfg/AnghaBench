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
struct nvkm_ram {int dummy; } ;
struct nvkm_fb {int dummy; } ;

/* Variables and functions */
 int gk104_ram_new_ (int /*<<< orphan*/ *,struct nvkm_fb*,struct nvkm_ram**) ; 
 int /*<<< orphan*/  gm200_ram ; 

int
gm200_ram_new(struct nvkm_fb *fb, struct nvkm_ram **pram)
{
	return gk104_ram_new_(&gm200_ram, fb, pram);
}