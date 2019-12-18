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
struct lantiq_ssc_spi {int /*<<< orphan*/  bits_per_word; struct lantiq_ssc_hwcfg* hwcfg; } ;
struct lantiq_ssc_hwcfg {int irnen_t; int irnen_r; } ;

/* Variables and functions */
 int /*<<< orphan*/  LTQ_SPI_CLC ; 
 int LTQ_SPI_CLC_RMC_S ; 
 int /*<<< orphan*/  LTQ_SPI_CON ; 
 int LTQ_SPI_CON_AEN ; 
 int LTQ_SPI_CON_REN ; 
 int LTQ_SPI_CON_RUEN ; 
 int LTQ_SPI_CON_RXOFF ; 
 int LTQ_SPI_CON_TEN ; 
 int LTQ_SPI_CON_TXOFF ; 
 int /*<<< orphan*/  LTQ_SPI_FPGO ; 
 int /*<<< orphan*/  LTQ_SPI_GPOCON ; 
 int /*<<< orphan*/  LTQ_SPI_IRNEN ; 
 int LTQ_SPI_IRNEN_E ; 
 int /*<<< orphan*/  LTQ_SPI_WHBSTATE ; 
 int LTQ_SPI_WHBSTATE_CLR_ERRORS ; 
 int LTQ_SPI_WHBSTATE_SETMS ; 
 int /*<<< orphan*/  SPI_MODE_0 ; 
 int /*<<< orphan*/  hw_enter_config_mode (struct lantiq_ssc_spi const*) ; 
 int /*<<< orphan*/  hw_setup_bits_per_word (struct lantiq_ssc_spi const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hw_setup_clock_mode (struct lantiq_ssc_spi const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lantiq_ssc_maskl (struct lantiq_ssc_spi const*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lantiq_ssc_writel (struct lantiq_ssc_spi const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rx_fifo_reset (struct lantiq_ssc_spi const*) ; 
 int /*<<< orphan*/  tx_fifo_reset (struct lantiq_ssc_spi const*) ; 

__attribute__((used)) static void lantiq_ssc_hw_init(const struct lantiq_ssc_spi *spi)
{
	const struct lantiq_ssc_hwcfg *hwcfg = spi->hwcfg;

	/*
	 * Set clock divider for run mode to 1 to
	 * run at same frequency as FPI bus
	 */
	lantiq_ssc_writel(spi, 1 << LTQ_SPI_CLC_RMC_S, LTQ_SPI_CLC);

	/* Put controller into config mode */
	hw_enter_config_mode(spi);

	/* Clear error flags */
	lantiq_ssc_maskl(spi, 0, LTQ_SPI_WHBSTATE_CLR_ERRORS, LTQ_SPI_WHBSTATE);

	/* Enable error checking, disable TX/RX */
	lantiq_ssc_writel(spi, LTQ_SPI_CON_RUEN | LTQ_SPI_CON_AEN |
		LTQ_SPI_CON_TEN | LTQ_SPI_CON_REN | LTQ_SPI_CON_TXOFF |
		LTQ_SPI_CON_RXOFF, LTQ_SPI_CON);

	/* Setup default SPI mode */
	hw_setup_bits_per_word(spi, spi->bits_per_word);
	hw_setup_clock_mode(spi, SPI_MODE_0);

	/* Enable master mode and clear error flags */
	lantiq_ssc_writel(spi, LTQ_SPI_WHBSTATE_SETMS |
			       LTQ_SPI_WHBSTATE_CLR_ERRORS,
			       LTQ_SPI_WHBSTATE);

	/* Reset GPIO/CS registers */
	lantiq_ssc_writel(spi, 0, LTQ_SPI_GPOCON);
	lantiq_ssc_writel(spi, 0xFF00, LTQ_SPI_FPGO);

	/* Enable and flush FIFOs */
	rx_fifo_reset(spi);
	tx_fifo_reset(spi);

	/* Enable interrupts */
	lantiq_ssc_writel(spi, hwcfg->irnen_t | hwcfg->irnen_r |
			  LTQ_SPI_IRNEN_E, LTQ_SPI_IRNEN);
}