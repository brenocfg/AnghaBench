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
struct TYPE_2__ {int speed; } ;
struct scc_channel {int clock; int /*<<< orphan*/  lock; TYPE_1__ modem; } ;

/* Variables and functions */
 int /*<<< orphan*/  set_brg (struct scc_channel*,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static inline void set_speed(struct scc_channel *scc)
{
	unsigned long flags;
	spin_lock_irqsave(&scc->lock, flags);

	if (scc->modem.speed > 0)	/* paranoia... */
		set_brg(scc, (unsigned) (scc->clock / (scc->modem.speed * 64)) - 2);
		
	spin_unlock_irqrestore(&scc->lock, flags);
}