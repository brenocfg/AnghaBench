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
struct nvkm_ior {int dummy; } ;
struct nvkm_head {int dummy; } ;
struct nv50_disp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HEAD_DBG (struct nvkm_head*,char*) ; 
 int /*<<< orphan*/  nv50_disp_super_ied_off (struct nvkm_head*,struct nvkm_ior*,int) ; 
 struct nvkm_ior* nv50_disp_super_ior_arm (struct nvkm_head*) ; 

void
nv50_disp_super_1_0(struct nv50_disp *disp, struct nvkm_head *head)
{
	struct nvkm_ior *ior;

	/* Determine which OR, if any, we're detaching from the head. */
	HEAD_DBG(head, "supervisor 1.0");
	ior = nv50_disp_super_ior_arm(head);
	if (!ior)
		return;

	/* Execute OffInt1 IED script. */
	nv50_disp_super_ied_off(head, ior, 1);
}