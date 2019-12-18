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
struct lantiq_ssc_spi {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LTQ_SPI_TXFCON ; 
 int LTQ_SPI_TXFCON_TXFEN ; 
 int LTQ_SPI_TXFCON_TXFITL_S ; 
 int LTQ_SPI_TXFCON_TXFLU ; 
 int /*<<< orphan*/  lantiq_ssc_writel (struct lantiq_ssc_spi const*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tx_fifo_reset(const struct lantiq_ssc_spi *spi)
{
	u32 val = 1 << LTQ_SPI_TXFCON_TXFITL_S;

	val |= LTQ_SPI_TXFCON_TXFEN | LTQ_SPI_TXFCON_TXFLU;
	lantiq_ssc_writel(spi, val, LTQ_SPI_TXFCON);
}