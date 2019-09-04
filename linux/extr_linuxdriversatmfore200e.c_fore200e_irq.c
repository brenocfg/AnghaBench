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
struct fore200e {int /*<<< orphan*/  q_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  fore200e_rx_irq (struct fore200e*) ; 
 int /*<<< orphan*/  fore200e_tx_irq (struct fore200e*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void
fore200e_irq(struct fore200e* fore200e)
{
    unsigned long flags;

    spin_lock_irqsave(&fore200e->q_lock, flags);
    fore200e_rx_irq(fore200e);
    spin_unlock_irqrestore(&fore200e->q_lock, flags);

    spin_lock_irqsave(&fore200e->q_lock, flags);
    fore200e_tx_irq(fore200e);
    spin_unlock_irqrestore(&fore200e->q_lock, flags);
}