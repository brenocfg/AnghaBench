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
struct sdio_uart_port {scalar_t__ in_sdio_uart_irq; int /*<<< orphan*/  func; } ;

/* Variables and functions */
 scalar_t__ current ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  sdio_release_host (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void sdio_uart_release_func(struct sdio_uart_port *port)
{
	if (likely(port->in_sdio_uart_irq != current))
		sdio_release_host(port->func);
}