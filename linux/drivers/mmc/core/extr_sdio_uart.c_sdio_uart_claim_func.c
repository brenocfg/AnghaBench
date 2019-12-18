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
struct sdio_uart_port {scalar_t__ in_sdio_uart_irq; int /*<<< orphan*/  func_lock; int /*<<< orphan*/  func; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ current ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdio_claim_host (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int sdio_uart_claim_func(struct sdio_uart_port *port)
{
	mutex_lock(&port->func_lock);
	if (unlikely(!port->func)) {
		mutex_unlock(&port->func_lock);
		return -ENODEV;
	}
	if (likely(port->in_sdio_uart_irq != current))
		sdio_claim_host(port->func);
	mutex_unlock(&port->func_lock);
	return 0;
}