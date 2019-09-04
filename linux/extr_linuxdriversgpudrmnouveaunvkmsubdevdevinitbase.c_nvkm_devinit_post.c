#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct nvkm_devinit {int /*<<< orphan*/  post; TYPE_1__* func; } ;
struct TYPE_2__ {int (* post ) (struct nvkm_devinit*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  nvkm_devinit_disable (struct nvkm_devinit*) ; 
 int stub1 (struct nvkm_devinit*,int /*<<< orphan*/ ) ; 

int
nvkm_devinit_post(struct nvkm_devinit *init, u64 *disable)
{
	int ret = 0;
	if (init && init->func->post)
		ret = init->func->post(init, init->post);
	*disable = nvkm_devinit_disable(init);
	return ret;
}