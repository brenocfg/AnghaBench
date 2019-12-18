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
struct nvkm_fifo {int /*<<< orphan*/  cevent; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvkm_event_send (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
nvkm_fifo_cevent(struct nvkm_fifo *fifo)
{
	nvkm_event_send(&fifo->cevent, 1, 0, NULL, 0);
}