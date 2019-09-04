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
struct nvkm_subdev {int dummy; } ;
struct nvkm_devinit {int post; } ;

/* Variables and functions */
 struct nvkm_devinit* nvkm_devinit (struct nvkm_subdev*) ; 

__attribute__((used)) static int
nvkm_devinit_fini(struct nvkm_subdev *subdev, bool suspend)
{
	struct nvkm_devinit *init = nvkm_devinit(subdev);
	/* force full reinit on resume */
	if (suspend)
		init->post = true;
	return 0;
}