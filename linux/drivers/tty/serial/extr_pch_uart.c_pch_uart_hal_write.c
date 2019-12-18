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
struct eg20t_port {scalar_t__ membase; } ;

/* Variables and functions */
 scalar_t__ PCH_UART_THR ; 
 int /*<<< orphan*/  iowrite8 (unsigned int,scalar_t__) ; 

__attribute__((used)) static void pch_uart_hal_write(struct eg20t_port *priv,
			      const unsigned char *buf, int tx_size)
{
	int i;
	unsigned int thr;

	for (i = 0; i < tx_size;) {
		thr = buf[i++];
		iowrite8(thr, priv->membase + PCH_UART_THR);
	}
}