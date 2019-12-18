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
typedef  int u32 ;

/* Variables and functions */
 int MTK_SPI_PACKET_SIZE ; 

__attribute__((used)) static int mtk_spi_get_mult_delta(u32 xfer_len)
{
	u32 mult_delta;

	if (xfer_len > MTK_SPI_PACKET_SIZE)
		mult_delta = xfer_len % MTK_SPI_PACKET_SIZE;
	else
		mult_delta = 0;

	return mult_delta;
}