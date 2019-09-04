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
struct nvkm_outp {TYPE_2__* func; } ;
struct TYPE_3__ {int head; struct nvkm_outp* outp; } ;
struct nvkm_ior {TYPE_1__ arm; } ;
struct nvkm_head {int id; } ;
struct nv50_disp {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* disable ) (struct nvkm_outp*,struct nvkm_ior*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  HEAD_DBG (struct nvkm_head*,char*) ; 
 int /*<<< orphan*/  nv50_disp_super_ied_off (struct nvkm_head*,struct nvkm_ior*,int) ; 
 struct nvkm_ior* nv50_disp_super_ior_arm (struct nvkm_head*) ; 
 int /*<<< orphan*/  stub1 (struct nvkm_outp*,struct nvkm_ior*) ; 

void
nv50_disp_super_2_0(struct nv50_disp *disp, struct nvkm_head *head)
{
	struct nvkm_outp *outp;
	struct nvkm_ior *ior;

	/* Determine which OR, if any, we're detaching from the head. */
	HEAD_DBG(head, "supervisor 2.0");
	ior = nv50_disp_super_ior_arm(head);
	if (!ior)
		return;

	/* Execute OffInt2 IED script. */
	nv50_disp_super_ied_off(head, ior, 2);

	/* If we're shutting down the OR's only active head, execute
	 * the output path's disable function.
	 */
	if (ior->arm.head == (1 << head->id)) {
		if ((outp = ior->arm.outp) && outp->func->disable)
			outp->func->disable(outp, ior);
	}
}