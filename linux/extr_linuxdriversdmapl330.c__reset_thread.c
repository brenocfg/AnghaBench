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
struct pl330_thread {int id; int req_running; TYPE_1__* req; struct pl330_dmac* dmac; } ;
struct pl330_dmac {int mcbufsz; scalar_t__ mcode_bus; scalar_t__ mcode_cpu; } ;
struct TYPE_2__ {int /*<<< orphan*/ * desc; scalar_t__ mc_bus; scalar_t__ mc_cpu; } ;

/* Variables and functions */

__attribute__((used)) static inline void _reset_thread(struct pl330_thread *thrd)
{
	struct pl330_dmac *pl330 = thrd->dmac;

	thrd->req[0].mc_cpu = pl330->mcode_cpu
				+ (thrd->id * pl330->mcbufsz);
	thrd->req[0].mc_bus = pl330->mcode_bus
				+ (thrd->id * pl330->mcbufsz);
	thrd->req[0].desc = NULL;

	thrd->req[1].mc_cpu = thrd->req[0].mc_cpu
				+ pl330->mcbufsz / 2;
	thrd->req[1].mc_bus = thrd->req[0].mc_bus
				+ pl330->mcbufsz / 2;
	thrd->req[1].desc = NULL;

	thrd->req_running = -1;
}