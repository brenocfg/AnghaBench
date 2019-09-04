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
struct pl330_thread {int id; int free; struct pl330_dmac* dmac; } ;
struct TYPE_2__ {int num_chan; } ;
struct pl330_dmac {struct pl330_thread* manager; struct pl330_thread* channels; TYPE_1__ pcfg; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  _reset_thread (struct pl330_thread*) ; 
 struct pl330_thread* kcalloc (int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dmac_alloc_threads(struct pl330_dmac *pl330)
{
	int chans = pl330->pcfg.num_chan;
	struct pl330_thread *thrd;
	int i;

	/* Allocate 1 Manager and 'chans' Channel threads */
	pl330->channels = kcalloc(1 + chans, sizeof(*thrd),
					GFP_KERNEL);
	if (!pl330->channels)
		return -ENOMEM;

	/* Init Channel threads */
	for (i = 0; i < chans; i++) {
		thrd = &pl330->channels[i];
		thrd->id = i;
		thrd->dmac = pl330;
		_reset_thread(thrd);
		thrd->free = true;
	}

	/* MANAGER is indexed at the end */
	thrd = &pl330->channels[chans];
	thrd->id = chans;
	thrd->dmac = pl330;
	thrd->free = false;
	pl330->manager = thrd;

	return 0;
}