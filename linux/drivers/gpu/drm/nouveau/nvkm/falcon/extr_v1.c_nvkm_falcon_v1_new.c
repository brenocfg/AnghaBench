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
struct nvkm_subdev {int dummy; } ;
struct nvkm_falcon {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct nvkm_falcon* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvkm_falcon_ctor (int /*<<< orphan*/ *,struct nvkm_subdev*,char const*,int /*<<< orphan*/ ,struct nvkm_falcon*) ; 
 int /*<<< orphan*/  nvkm_falcon_v1 ; 

int
nvkm_falcon_v1_new(struct nvkm_subdev *owner, const char *name, u32 addr,
		   struct nvkm_falcon **pfalcon)
{
	struct nvkm_falcon *falcon;
	if (!(falcon = *pfalcon = kzalloc(sizeof(*falcon), GFP_KERNEL)))
		return -ENOMEM;
	nvkm_falcon_ctor(&nvkm_falcon_v1, owner, name, addr, falcon);
	return 0;
}