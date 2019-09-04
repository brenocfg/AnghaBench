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
struct nvkm_fifo {int /*<<< orphan*/  uevent; } ;
struct nvif_notify_uevent_rep {int dummy; } ;
typedef  int /*<<< orphan*/  rep ;

/* Variables and functions */
 int /*<<< orphan*/  nvkm_event_send (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,struct nvif_notify_uevent_rep*,int) ; 

void
nvkm_fifo_uevent(struct nvkm_fifo *fifo)
{
	struct nvif_notify_uevent_rep rep = {
	};
	nvkm_event_send(&fifo->uevent, 1, 0, &rep, sizeof(rep));
}