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
typedef  int u32 ;
struct uniphier8250_priv {int /*<<< orphan*/  atomic_write_lock; } ;
struct uart_port {scalar_t__ membase; struct uniphier8250_priv* private_data; } ;

/* Variables and functions */
#define  UART_FCR 131 
#define  UART_LCR 130 
 int UART_LCR_DLAB ; 
#define  UART_MCR 129 
#define  UART_SCR 128 
 int UNIPHIER_UART_CHAR_FCR ; 
 int UNIPHIER_UART_LCR_MCR ; 
 int UNIPHIER_UART_REGSHIFT ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void uniphier_serial_out(struct uart_port *p, int offset, int value)
{
	unsigned int valshift = 0;
	bool normal = false;

	switch (offset) {
	case UART_SCR:
		/* No SCR for this hardware.  Use CHAR as a scratch register */
		valshift = 8;
		/* fall through */
	case UART_FCR:
		offset = UNIPHIER_UART_CHAR_FCR;
		break;
	case UART_LCR:
		valshift = 8;
		/* Divisor latch access bit does not exist. */
		value &= ~UART_LCR_DLAB;
		/* fall through */
	case UART_MCR:
		offset = UNIPHIER_UART_LCR_MCR;
		break;
	default:
		offset <<= UNIPHIER_UART_REGSHIFT;
		normal = true;
		break;
	}

	if (normal) {
		writel(value, p->membase + offset);
	} else {
		/*
		 * Special case: two registers share the same address that
		 * must be 32-bit accessed.  As this is not longer atomic safe,
		 * take a lock just in case.
		 */
		struct uniphier8250_priv *priv = p->private_data;
		unsigned long flags;
		u32 tmp;

		spin_lock_irqsave(&priv->atomic_write_lock, flags);
		tmp = readl(p->membase + offset);
		tmp &= ~(0xff << valshift);
		tmp |= value << valshift;
		writel(tmp, p->membase + offset);
		spin_unlock_irqrestore(&priv->atomic_write_lock, flags);
	}
}