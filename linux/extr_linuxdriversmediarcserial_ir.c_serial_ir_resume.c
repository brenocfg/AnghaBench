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
struct platform_device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;
struct TYPE_3__ {int /*<<< orphan*/  lastkt; } ;

/* Variables and functions */
 int /*<<< orphan*/  UART_IER ; 
 int UART_IER_MSI ; 
 TYPE_2__* hardware ; 
 int hardware_init_port () ; 
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  off () ; 
 TYPE_1__ serial_ir ; 
 int sinp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  soutp (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 size_t type ; 

__attribute__((used)) static int serial_ir_resume(struct platform_device *dev)
{
	unsigned long flags;
	int result;

	result = hardware_init_port();
	if (result < 0)
		return result;

	spin_lock_irqsave(&hardware[type].lock, flags);
	/* Enable Interrupt */
	serial_ir.lastkt = ktime_get();
	soutp(UART_IER, sinp(UART_IER) | UART_IER_MSI);
	off();

	spin_unlock_irqrestore(&hardware[type].lock, flags);

	return 0;
}