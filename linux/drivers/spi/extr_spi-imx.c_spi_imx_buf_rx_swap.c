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
typedef  int u8 ;
typedef  int u32 ;
struct spi_imx_data {int remainder; scalar_t__ rx_buf; scalar_t__ base; int /*<<< orphan*/  bits_per_word; } ;

/* Variables and functions */
 scalar_t__ MXC_CSPIRXDATA ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  spi_imx_buf_rx_swap_u32 (struct spi_imx_data*) ; 
 int /*<<< orphan*/  spi_imx_buf_rx_u16 (struct spi_imx_data*) ; 
 int spi_imx_bytes_per_word (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void spi_imx_buf_rx_swap(struct spi_imx_data *spi_imx)
{
	int unaligned;
	u32 val;

	unaligned = spi_imx->remainder % 4;

	if (!unaligned) {
		spi_imx_buf_rx_swap_u32(spi_imx);
		return;
	}

	if (spi_imx_bytes_per_word(spi_imx->bits_per_word) == 2) {
		spi_imx_buf_rx_u16(spi_imx);
		return;
	}

	val = readl(spi_imx->base + MXC_CSPIRXDATA);

	while (unaligned--) {
		if (spi_imx->rx_buf) {
			*(u8 *)spi_imx->rx_buf = (val >> (8 * unaligned)) & 0xff;
			spi_imx->rx_buf++;
		}
		spi_imx->remainder--;
	}
}