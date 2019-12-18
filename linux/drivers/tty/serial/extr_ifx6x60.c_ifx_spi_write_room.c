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
struct tty_struct {struct ifx_spi_device* driver_data; } ;
struct ifx_spi_device {int /*<<< orphan*/  tx_fifo; } ;

/* Variables and functions */
 int IFX_SPI_FIFO_SIZE ; 
 int kfifo_len (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ifx_spi_write_room(struct tty_struct *tty)
{
	struct ifx_spi_device *ifx_dev = tty->driver_data;
	return IFX_SPI_FIFO_SIZE - kfifo_len(&ifx_dev->tx_fifo);
}