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
typedef  int u32 ;
typedef  int u16 ;
struct spi_message {struct spi_device* spi; } ;
struct spi_master {int dummy; } ;
struct spi_device {int mode; size_t chip_select; struct mtk_chip_config* controller_data; } ;
struct mtk_spi {int* pad_sel; scalar_t__ base; TYPE_1__* dev_comp; } ;
struct mtk_chip_config {scalar_t__ sample_sel; scalar_t__ cs_pol; } ;
struct TYPE_2__ {scalar_t__ need_pad_sel; scalar_t__ enhance_timing; } ;

/* Variables and functions */
 int SPI_CMD_CPHA ; 
 int SPI_CMD_CPOL ; 
 int SPI_CMD_CS_POL ; 
 int SPI_CMD_DEASSERT ; 
 int SPI_CMD_FINISH_IE ; 
 int SPI_CMD_PAUSE_IE ; 
 scalar_t__ SPI_CMD_REG ; 
 int SPI_CMD_RXMSBF ; 
 int SPI_CMD_RX_DMA ; 
 int SPI_CMD_RX_ENDIAN ; 
 int SPI_CMD_SAMPLE_SEL ; 
 int SPI_CMD_TXMSBF ; 
 int SPI_CMD_TX_DMA ; 
 int SPI_CMD_TX_ENDIAN ; 
 int SPI_CPHA ; 
 int SPI_CPOL ; 
 int SPI_LSB_FIRST ; 
 scalar_t__ SPI_PAD_SEL_REG ; 
 int readl (scalar_t__) ; 
 struct mtk_spi* spi_master_get_devdata (struct spi_master*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int mtk_spi_prepare_message(struct spi_master *master,
				   struct spi_message *msg)
{
	u16 cpha, cpol;
	u32 reg_val;
	struct spi_device *spi = msg->spi;
	struct mtk_chip_config *chip_config = spi->controller_data;
	struct mtk_spi *mdata = spi_master_get_devdata(master);

	cpha = spi->mode & SPI_CPHA ? 1 : 0;
	cpol = spi->mode & SPI_CPOL ? 1 : 0;

	reg_val = readl(mdata->base + SPI_CMD_REG);
	if (cpha)
		reg_val |= SPI_CMD_CPHA;
	else
		reg_val &= ~SPI_CMD_CPHA;
	if (cpol)
		reg_val |= SPI_CMD_CPOL;
	else
		reg_val &= ~SPI_CMD_CPOL;

	/* set the mlsbx and mlsbtx */
	if (spi->mode & SPI_LSB_FIRST) {
		reg_val &= ~SPI_CMD_TXMSBF;
		reg_val &= ~SPI_CMD_RXMSBF;
	} else {
		reg_val |= SPI_CMD_TXMSBF;
		reg_val |= SPI_CMD_RXMSBF;
	}

	/* set the tx/rx endian */
#ifdef __LITTLE_ENDIAN
	reg_val &= ~SPI_CMD_TX_ENDIAN;
	reg_val &= ~SPI_CMD_RX_ENDIAN;
#else
	reg_val |= SPI_CMD_TX_ENDIAN;
	reg_val |= SPI_CMD_RX_ENDIAN;
#endif

	if (mdata->dev_comp->enhance_timing) {
		if (chip_config->cs_pol)
			reg_val |= SPI_CMD_CS_POL;
		else
			reg_val &= ~SPI_CMD_CS_POL;
		if (chip_config->sample_sel)
			reg_val |= SPI_CMD_SAMPLE_SEL;
		else
			reg_val &= ~SPI_CMD_SAMPLE_SEL;
	}

	/* set finish and pause interrupt always enable */
	reg_val |= SPI_CMD_FINISH_IE | SPI_CMD_PAUSE_IE;

	/* disable dma mode */
	reg_val &= ~(SPI_CMD_TX_DMA | SPI_CMD_RX_DMA);

	/* disable deassert mode */
	reg_val &= ~SPI_CMD_DEASSERT;

	writel(reg_val, mdata->base + SPI_CMD_REG);

	/* pad select */
	if (mdata->dev_comp->need_pad_sel)
		writel(mdata->pad_sel[spi->chip_select],
		       mdata->base + SPI_PAD_SEL_REG);

	return 0;
}