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
struct spi_message {TYPE_1__* spi; } ;
struct spi_master {int dummy; } ;
struct qcom_qspi {int /*<<< orphan*/  lock; scalar_t__ base; } ;
struct TYPE_2__ {int mode; scalar_t__ chip_select; } ;

/* Variables and functions */
 int CHIP_SELECT_NUM ; 
 int DMA_ENABLE ; 
 int FB_CLK_EN ; 
 int FULL_CYCLE_MODE ; 
 scalar_t__ MSTR_CONFIG ; 
 int PIN_HOLDN ; 
 int PIN_WPN ; 
 int SBL_EN ; 
 int SPI_MODE_MSK ; 
 int SPI_MODE_SHFT ; 
 int TX_DATA_DELAY_MSK ; 
 int TX_DATA_DELAY_SHFT ; 
 int TX_DATA_OE_DELAY_MSK ; 
 int TX_DATA_OE_DELAY_SHFT ; 
 int readl (scalar_t__) ; 
 struct qcom_qspi* spi_master_get_devdata (struct spi_master*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int qcom_qspi_prepare_message(struct spi_master *master,
				     struct spi_message *message)
{
	u32 mstr_cfg;
	struct qcom_qspi *ctrl;
	int tx_data_oe_delay = 1;
	int tx_data_delay = 1;
	unsigned long flags;

	ctrl = spi_master_get_devdata(master);
	spin_lock_irqsave(&ctrl->lock, flags);

	mstr_cfg = readl(ctrl->base + MSTR_CONFIG);
	mstr_cfg &= ~CHIP_SELECT_NUM;
	if (message->spi->chip_select)
		mstr_cfg |= CHIP_SELECT_NUM;

	mstr_cfg |= FB_CLK_EN | PIN_WPN | PIN_HOLDN | SBL_EN | FULL_CYCLE_MODE;
	mstr_cfg &= ~(SPI_MODE_MSK | TX_DATA_OE_DELAY_MSK | TX_DATA_DELAY_MSK);
	mstr_cfg |= message->spi->mode << SPI_MODE_SHFT;
	mstr_cfg |= tx_data_oe_delay << TX_DATA_OE_DELAY_SHFT;
	mstr_cfg |= tx_data_delay << TX_DATA_DELAY_SHFT;
	mstr_cfg &= ~DMA_ENABLE;

	writel(mstr_cfg, ctrl->base + MSTR_CONFIG);
	spin_unlock_irqrestore(&ctrl->lock, flags);

	return 0;
}