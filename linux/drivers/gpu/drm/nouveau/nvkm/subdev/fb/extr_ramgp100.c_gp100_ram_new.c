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
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int gf100_ram_ctor (int /*<<< orphan*/ *,struct nvkm_fb*,struct nvkm_ram*) ; 
 int /*<<< orphan*/  gp100_ram ; 
 struct nvkm_ram* kzalloc (int,int /*<<< orphan*/ ) ; 

int
gp100_ram_new(struct nvkm_fb *fb, struct nvkm_ram **pram)
{
	struct nvkm_ram *ram;

	if (!(ram = *pram = kzalloc(sizeof(*ram), GFP_KERNEL)))
		return -ENOMEM;

	return gf100_ram_ctor(&gp100_ram, fb, ram);

}