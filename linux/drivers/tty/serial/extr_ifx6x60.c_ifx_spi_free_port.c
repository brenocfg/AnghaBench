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
struct ifx_spi_device {int /*<<< orphan*/  tx_fifo; int /*<<< orphan*/  tty_port; int /*<<< orphan*/  minor; scalar_t__ tty_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfifo_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_drv ; 
 int /*<<< orphan*/  tty_port_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_unregister_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ifx_spi_free_port(struct ifx_spi_device *ifx_dev)
{
	if (ifx_dev->tty_dev)
		tty_unregister_device(tty_drv, ifx_dev->minor);
	tty_port_destroy(&ifx_dev->tty_port);
	kfifo_free(&ifx_dev->tx_fifo);
}