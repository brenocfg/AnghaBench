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
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;
struct lpuart_port {TYPE_1__ port; } ;

/* Variables and functions */
 int /*<<< orphan*/  lpuart32_transmit_buffer (struct lpuart_port*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void lpuart32_txint(struct lpuart_port *sport)
{
	unsigned long flags;

	spin_lock_irqsave(&sport->port.lock, flags);
	lpuart32_transmit_buffer(sport);
	spin_unlock_irqrestore(&sport->port.lock, flags);
}