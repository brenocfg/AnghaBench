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
struct sdma_engine {int /*<<< orphan*/  tail_lock; } ;

/* Variables and functions */
 int __sdma_running (struct sdma_engine*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static inline int sdma_running(struct sdma_engine *engine)
{
	unsigned long flags;
	int ret;

	spin_lock_irqsave(&engine->tail_lock, flags);
	ret = __sdma_running(engine);
	spin_unlock_irqrestore(&engine->tail_lock, flags);
	return ret;
}