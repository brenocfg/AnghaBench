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
struct spi_message {struct spi_device* spi; } ;
struct spi_device {int mode; } ;
struct spi_controller {int dummy; } ;
struct mtk_spi_slave {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ SPIS_CFG_REG ; 
 int SPIS_CPHA ; 
 int SPIS_CPOL ; 
 int SPIS_RXMSBF ; 
 int SPIS_RX_ENDIAN ; 
 int SPIS_TXMSBF ; 
 int SPIS_TX_ENDIAN ; 
 int SPI_CPHA ; 
 int SPI_CPOL ; 
 int SPI_LSB_FIRST ; 
 int readl (scalar_t__) ; 
 struct mtk_spi_slave* spi_controller_get_devdata (struct spi_controller*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int mtk_spi_slave_prepare_message(struct spi_controller *ctlr,
					 struct spi_message *msg)
{
	struct mtk_spi_slave *mdata = spi_controller_get_devdata(ctlr);
	struct spi_device *spi = msg->spi;
	bool cpha, cpol;
	u32 reg_val;

	cpha = spi->mode & SPI_CPHA ? 1 : 0;
	cpol = spi->mode & SPI_CPOL ? 1 : 0;

	reg_val = readl(mdata->base + SPIS_CFG_REG);
	if (cpha)
		reg_val |= SPIS_CPHA;
	else
		reg_val &= ~SPIS_CPHA;
	if (cpol)
		reg_val |= SPIS_CPOL;
	else
		reg_val &= ~SPIS_CPOL;

	if (spi->mode & SPI_LSB_FIRST)
		reg_val &= ~(SPIS_TXMSBF | SPIS_RXMSBF);
	else
		reg_val |= SPIS_TXMSBF | SPIS_RXMSBF;

	reg_val &= ~SPIS_TX_ENDIAN;
	reg_val &= ~SPIS_RX_ENDIAN;
	writel(reg_val, mdata->base + SPIS_CFG_REG);

	return 0;
}