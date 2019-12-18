#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct nvkm_ior {TYPE_2__* func; } ;
struct TYPE_3__ {int hz; } ;
struct nvkm_head {TYPE_1__ asy; } ;
struct nv50_disp {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* war_3 ) (struct nvkm_ior*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  HEAD_DBG (struct nvkm_head*,char*) ; 
 int /*<<< orphan*/  nv50_disp_super_ied_on (struct nvkm_head*,struct nvkm_ior*,int,int) ; 
 struct nvkm_ior* nv50_disp_super_ior_asy (struct nvkm_head*) ; 
 int /*<<< orphan*/  stub1 (struct nvkm_ior*) ; 

void
nv50_disp_super_3_0(struct nv50_disp *disp, struct nvkm_head *head)
{
	struct nvkm_ior *ior;

	/* Determine which OR, if any, we're attaching to the head. */
	HEAD_DBG(head, "supervisor 3.0");
	ior = nv50_disp_super_ior_asy(head);
	if (!ior)
		return;

	/* Execute OnInt3 IED script. */
	nv50_disp_super_ied_on(head, ior, 1, head->asy.hz / 1000);

	/* OR-specific handling. */
	if (ior->func->war_3)
		ior->func->war_3(ior);
}