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
struct TYPE_2__ {scalar_t__ (* get_tick ) () ;} ;

/* Variables and functions */
 size_t MASTER ; 
 unsigned long NUM_ITERS ; 
 unsigned long NUM_ROUNDS ; 
 size_t SLAVE ; 
 scalar_t__* go ; 
 int /*<<< orphan*/  itc_sync_lock ; 
 int /*<<< orphan*/  membar_safe (char*) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  rmb () ; 
 int /*<<< orphan*/  smp_start_sync_tick_client (int) ; 
 scalar_t__ stub1 () ; 
 TYPE_1__* tick_ops ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void smp_synchronize_one_tick(int cpu)
{
	unsigned long flags, i;

	go[MASTER] = 0;

	smp_start_sync_tick_client(cpu);

	/* wait for client to be ready */
	while (!go[MASTER])
		rmb();

	/* now let the client proceed into his loop */
	go[MASTER] = 0;
	membar_safe("#StoreLoad");

	raw_spin_lock_irqsave(&itc_sync_lock, flags);
	{
		for (i = 0; i < NUM_ROUNDS*NUM_ITERS; i++) {
			while (!go[MASTER])
				rmb();
			go[MASTER] = 0;
			wmb();
			go[SLAVE] = tick_ops->get_tick();
			membar_safe("#StoreLoad");
		}
	}
	raw_spin_unlock_irqrestore(&itc_sync_lock, flags);
}