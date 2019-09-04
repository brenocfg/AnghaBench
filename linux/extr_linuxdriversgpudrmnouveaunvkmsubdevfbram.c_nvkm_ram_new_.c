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
typedef  int /*<<< orphan*/  u64 ;
struct nvkm_ram_func {int dummy; } ;
struct nvkm_ram {int dummy; } ;
struct nvkm_fb {int dummy; } ;
typedef  enum nvkm_ram_type { ____Placeholder_nvkm_ram_type } nvkm_ram_type ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct nvkm_ram* kzalloc (int,int /*<<< orphan*/ ) ; 
 int nvkm_ram_ctor (struct nvkm_ram_func const*,struct nvkm_fb*,int,int /*<<< orphan*/ ,struct nvkm_ram*) ; 

int
nvkm_ram_new_(const struct nvkm_ram_func *func, struct nvkm_fb *fb,
	      enum nvkm_ram_type type, u64 size, struct nvkm_ram **pram)
{
	if (!(*pram = kzalloc(sizeof(**pram), GFP_KERNEL)))
		return -ENOMEM;
	return nvkm_ram_ctor(func, fb, type, size, *pram);
}