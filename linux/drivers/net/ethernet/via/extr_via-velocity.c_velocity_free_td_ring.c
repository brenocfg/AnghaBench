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
struct TYPE_4__ {int numq; int /*<<< orphan*/ ** infos; } ;
struct TYPE_3__ {int numtx; } ;
struct velocity_info {TYPE_2__ tx; TYPE_1__ options; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  velocity_free_td_ring_entry (struct velocity_info*,int,int) ; 

__attribute__((used)) static void velocity_free_td_ring(struct velocity_info *vptr)
{
	int i, j;

	for (j = 0; j < vptr->tx.numq; j++) {
		if (vptr->tx.infos[j] == NULL)
			continue;
		for (i = 0; i < vptr->options.numtx; i++)
			velocity_free_td_ring_entry(vptr, j, i);

		kfree(vptr->tx.infos[j]);
		vptr->tx.infos[j] = NULL;
	}
}