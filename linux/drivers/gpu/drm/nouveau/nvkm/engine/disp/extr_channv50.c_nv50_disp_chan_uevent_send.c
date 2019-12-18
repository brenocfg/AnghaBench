#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct nvif_notify_uevent_rep   TYPE_1__ ;

/* Type definitions */
struct nv50_disp {int /*<<< orphan*/  uevent; } ;
typedef  int /*<<< orphan*/  rep ;
struct nvif_notify_uevent_rep {} ;

/* Variables and functions */
 int /*<<< orphan*/  nvkm_event_send (int /*<<< orphan*/ *,int,int,TYPE_1__*,int) ; 

void
nv50_disp_chan_uevent_send(struct nv50_disp *disp, int chid)
{
	struct nvif_notify_uevent_rep {
	} rep;

	nvkm_event_send(&disp->uevent, 1, chid, &rep, sizeof(rep));
}