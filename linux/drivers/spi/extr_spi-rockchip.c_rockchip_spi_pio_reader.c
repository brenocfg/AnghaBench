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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
typedef  scalar_t__ u16 ;
struct rockchip_spi {scalar_t__ rx_left; int n_bytes; scalar_t__ rx; scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ ROCKCHIP_SPI_RXDR ; 
 scalar_t__ ROCKCHIP_SPI_RXFLR ; 
 scalar_t__ ROCKCHIP_SPI_RXFTLR ; 
 scalar_t__ readl_relaxed (scalar_t__) ; 

__attribute__((used)) static void rockchip_spi_pio_reader(struct rockchip_spi *rs)
{
	u32 words = readl_relaxed(rs->regs + ROCKCHIP_SPI_RXFLR);
	u32 rx_left = rs->rx_left - words;

	/* the hardware doesn't allow us to change fifo threshold
	 * level while spi is enabled, so instead make sure to leave
	 * enough words in the rx fifo to get the last interrupt
	 * exactly when all words have been received
	 */
	if (rx_left) {
		u32 ftl = readl_relaxed(rs->regs + ROCKCHIP_SPI_RXFTLR) + 1;

		if (rx_left < ftl) {
			rx_left = ftl;
			words = rs->rx_left - rx_left;
		}
	}

	rs->rx_left = rx_left;
	for (; words; words--) {
		u32 rxw = readl_relaxed(rs->regs + ROCKCHIP_SPI_RXDR);

		if (!rs->rx)
			continue;

		if (rs->n_bytes == 1)
			*(u8 *)rs->rx = (u8)rxw;
		else
			*(u16 *)rs->rx = (u16)rxw;
		rs->rx += rs->n_bytes;
	}
}