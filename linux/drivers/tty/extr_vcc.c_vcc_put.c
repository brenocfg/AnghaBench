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
struct vcc_port {int excl_locked; int /*<<< orphan*/  refcnt; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  vcc_table_lock ; 

__attribute__((used)) static void vcc_put(struct vcc_port *port, bool excl)
{
	unsigned long flags;

	if (!port)
		return;

	spin_lock_irqsave(&vcc_table_lock, flags);

	/* check if caller attempted to put with the wrong flags */
	if (WARN_ON((excl && !port->excl_locked) ||
		    (!excl && port->excl_locked)))
		goto done;

	port->refcnt--;

	if (excl)
		port->excl_locked = false;

done:
	spin_unlock_irqrestore(&vcc_table_lock, flags);
}