#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
typedef  scalar_t__ u16 ;
struct sirfsoc_spi {int /*<<< orphan*/  left_rx_word; scalar_t__* rx; TYPE_1__* regs; scalar_t__ base; } ;
struct TYPE_2__ {scalar_t__ rxfifo_data; } ;

/* Variables and functions */
 scalar_t__ readl (scalar_t__) ; 

__attribute__((used)) static void spi_sirfsoc_rx_word_u16(struct sirfsoc_spi *sspi)
{
	u32 data;
	u16 *rx = sspi->rx;

	data = readl(sspi->base + sspi->regs->rxfifo_data);

	if (rx) {
		*rx++ = (u16) data;
		sspi->rx = rx;
	}

	sspi->left_rx_word--;
}