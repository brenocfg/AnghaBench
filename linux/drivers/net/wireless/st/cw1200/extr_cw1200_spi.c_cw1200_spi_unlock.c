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
struct hwbus_priv {int /*<<< orphan*/  wq; int /*<<< orphan*/  lock; scalar_t__ claimed; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cw1200_spi_unlock(struct hwbus_priv *self)
{
	unsigned long flags;

	spin_lock_irqsave(&self->lock, flags);
	self->claimed = 0;
	spin_unlock_irqrestore(&self->lock, flags);
	wake_up(&self->wq);

	return;
}