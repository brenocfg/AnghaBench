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
struct vcc_port {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  VCC_CTL_HUP ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  vcc_kick_tx (struct vcc_port*) ; 
 scalar_t__ vcc_send_ctl (struct vcc_port*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vcc_ldc_hup(struct vcc_port *port)
{
	unsigned long flags;

	spin_lock_irqsave(&port->lock, flags);

	if (vcc_send_ctl(port, VCC_CTL_HUP) < 0)
		vcc_kick_tx(port);

	spin_unlock_irqrestore(&port->lock, flags);
}