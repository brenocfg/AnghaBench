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
struct i2400m {int /*<<< orphan*/  rx_lock; int /*<<< orphan*/  rx_roq_refcount; scalar_t__ rx_reorder; } ;

/* Variables and functions */
 int /*<<< orphan*/  i2400m_report_hook_flush (struct i2400m*) ; 
 int /*<<< orphan*/  i2400m_rx_roq_destroy ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void i2400m_rx_release(struct i2400m *i2400m)
{
	unsigned long flags;

	if (i2400m->rx_reorder) {
		spin_lock_irqsave(&i2400m->rx_lock, flags);
		kref_put(&i2400m->rx_roq_refcount, i2400m_rx_roq_destroy);
		spin_unlock_irqrestore(&i2400m->rx_lock, flags);
	}
	/* at this point, nothing can be received... */
	i2400m_report_hook_flush(i2400m);
}