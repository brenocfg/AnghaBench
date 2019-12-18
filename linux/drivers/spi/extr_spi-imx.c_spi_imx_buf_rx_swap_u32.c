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
typedef  unsigned int u32 ;
struct spi_imx_data {int remainder; scalar_t__ rx_buf; int /*<<< orphan*/  bits_per_word; scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ MXC_CSPIRXDATA ; 
 unsigned int cpu_to_be32 (unsigned int) ; 
 unsigned int readl (scalar_t__) ; 
 unsigned int spi_imx_bytes_per_word (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void spi_imx_buf_rx_swap_u32(struct spi_imx_data *spi_imx)
{
	unsigned int val = readl(spi_imx->base + MXC_CSPIRXDATA);
#ifdef __LITTLE_ENDIAN
	unsigned int bytes_per_word;
#endif

	if (spi_imx->rx_buf) {
#ifdef __LITTLE_ENDIAN
		bytes_per_word = spi_imx_bytes_per_word(spi_imx->bits_per_word);
		if (bytes_per_word == 1)
			val = cpu_to_be32(val);
		else if (bytes_per_word == 2)
			val = (val << 16) | (val >> 16);
#endif
		*(u32 *)spi_imx->rx_buf = val;
		spi_imx->rx_buf += sizeof(u32);
	}

	spi_imx->remainder -= sizeof(u32);
}