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
struct velocity_td_info {int dummy; } ;
struct TYPE_4__ {int numq; scalar_t__* used; scalar_t__* curr; scalar_t__* tail; int /*<<< orphan*/ * infos; } ;
struct TYPE_3__ {int /*<<< orphan*/  numtx; } ;
struct velocity_info {TYPE_2__ tx; TYPE_1__ options; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kcalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int velocity_init_td_ring(struct velocity_info *vptr)
{
	int j;

	/* Init the TD ring entries */
	for (j = 0; j < vptr->tx.numq; j++) {

		vptr->tx.infos[j] = kcalloc(vptr->options.numtx,
					    sizeof(struct velocity_td_info),
					    GFP_KERNEL);
		if (!vptr->tx.infos[j])	{
			while (--j >= 0)
				kfree(vptr->tx.infos[j]);
			return -ENOMEM;
		}

		vptr->tx.tail[j] = vptr->tx.curr[j] = vptr->tx.used[j] = 0;
	}
	return 0;
}