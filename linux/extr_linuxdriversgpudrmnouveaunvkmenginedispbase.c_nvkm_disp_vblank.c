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
struct nvkm_disp {int /*<<< orphan*/  vblank; } ;
struct nvif_notify_head_rep_v0 {int dummy; } ;
typedef  int /*<<< orphan*/  rep ;

/* Variables and functions */
 int /*<<< orphan*/  nvkm_event_send (int /*<<< orphan*/ *,int,int,struct nvif_notify_head_rep_v0*,int) ; 

void
nvkm_disp_vblank(struct nvkm_disp *disp, int head)
{
	struct nvif_notify_head_rep_v0 rep = {};
	nvkm_event_send(&disp->vblank, 1, head, &rep, sizeof(rep));
}