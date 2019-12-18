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
struct ifx_spi_device {int /*<<< orphan*/  signal_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFX_SPI_CTS ; 
 int /*<<< orphan*/  IFX_SPI_DCD ; 
 int /*<<< orphan*/  IFX_SPI_DSR ; 
 int /*<<< orphan*/  IFX_SPI_DTR ; 
 int /*<<< orphan*/  IFX_SPI_RI ; 
 int /*<<< orphan*/  IFX_SPI_RTS ; 
 unsigned int TIOCM_CAR ; 
 unsigned int TIOCM_CTS ; 
 unsigned int TIOCM_DSR ; 
 unsigned int TIOCM_DTR ; 
 unsigned int TIOCM_RNG ; 
 unsigned int TIOCM_RTS ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ifx_spi_tiocmget(struct tty_struct *tty)
{
	unsigned int value;
	struct ifx_spi_device *ifx_dev = tty->driver_data;

	value =
	(test_bit(IFX_SPI_RTS, &ifx_dev->signal_state) ? TIOCM_RTS : 0) |
	(test_bit(IFX_SPI_DTR, &ifx_dev->signal_state) ? TIOCM_DTR : 0) |
	(test_bit(IFX_SPI_CTS, &ifx_dev->signal_state) ? TIOCM_CTS : 0) |
	(test_bit(IFX_SPI_DSR, &ifx_dev->signal_state) ? TIOCM_DSR : 0) |
	(test_bit(IFX_SPI_DCD, &ifx_dev->signal_state) ? TIOCM_CAR : 0) |
	(test_bit(IFX_SPI_RI, &ifx_dev->signal_state) ? TIOCM_RNG : 0);
	return value;
}