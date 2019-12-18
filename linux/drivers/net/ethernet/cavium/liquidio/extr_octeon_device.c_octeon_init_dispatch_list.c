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
typedef  size_t u32 ;
struct TYPE_3__ {int /*<<< orphan*/  lock; TYPE_2__* dlist; scalar_t__ count; } ;
struct octeon_device {TYPE_1__ dispatch; } ;
struct TYPE_4__ {int /*<<< orphan*/  list; scalar_t__ opcode; } ;

/* Variables and functions */
 size_t DISPATCH_LIST_SIZE ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 size_t REQTYPE_LAST ; 
 int /*<<< orphan*/  octeon_register_reqtype_free_fn (struct octeon_device*,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int octeon_init_dispatch_list(struct octeon_device *oct)
{
	u32 i;

	oct->dispatch.count = 0;

	for (i = 0; i < DISPATCH_LIST_SIZE; i++) {
		oct->dispatch.dlist[i].opcode = 0;
		INIT_LIST_HEAD(&oct->dispatch.dlist[i].list);
	}

	for (i = 0; i <= REQTYPE_LAST; i++)
		octeon_register_reqtype_free_fn(oct, i, NULL);

	spin_lock_init(&oct->dispatch.lock);

	return 0;
}