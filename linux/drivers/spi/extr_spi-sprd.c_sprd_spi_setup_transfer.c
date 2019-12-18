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
typedef  int u8 ;
typedef  int u32 ;
struct TYPE_2__ {int fragmens_len; int /*<<< orphan*/  width; } ;
struct sprd_spi {int len; int trans_len; int trans_mode; int /*<<< orphan*/  write_bufs; scalar_t__ base; TYPE_1__ dma; int /*<<< orphan*/  read_bufs; int /*<<< orphan*/  hw_mode; scalar_t__ rx_buf; scalar_t__ tx_buf; } ;
struct spi_transfer {int bits_per_word; int len; scalar_t__ rx_buf; scalar_t__ tx_buf; int /*<<< orphan*/  speed_hz; } ;
struct spi_device {int /*<<< orphan*/  mode; int /*<<< orphan*/  controller; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_SLAVE_BUSWIDTH_1_BYTE ; 
 int /*<<< orphan*/  DMA_SLAVE_BUSWIDTH_2_BYTES ; 
 int /*<<< orphan*/  DMA_SLAVE_BUSWIDTH_4_BYTES ; 
 int EINVAL ; 
 scalar_t__ SPRD_SPI_CTL1 ; 
 int SPRD_SPI_DMA_STEP ; 
 int SPRD_SPI_RTX_MD_MASK ; 
 int SPRD_SPI_RX_MODE ; 
 int SPRD_SPI_TX_MODE ; 
 int readl_relaxed (scalar_t__) ; 
 int round_up (int,int) ; 
 struct sprd_spi* spi_controller_get_devdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprd_spi_init_hw (struct sprd_spi*,struct spi_transfer*) ; 
 int /*<<< orphan*/  sprd_spi_read_bufs_u16 ; 
 int /*<<< orphan*/  sprd_spi_read_bufs_u32 ; 
 int /*<<< orphan*/  sprd_spi_read_bufs_u8 ; 
 int /*<<< orphan*/  sprd_spi_set_speed (struct sprd_spi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprd_spi_set_transfer_bits (struct sprd_spi*,int) ; 
 int /*<<< orphan*/  sprd_spi_write_bufs_u16 ; 
 int /*<<< orphan*/  sprd_spi_write_bufs_u32 ; 
 int /*<<< orphan*/  sprd_spi_write_bufs_u8 ; 
 int /*<<< orphan*/  sprd_spi_write_only_receive ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static int sprd_spi_setup_transfer(struct spi_device *sdev,
				   struct spi_transfer *t)
{
	struct sprd_spi *ss = spi_controller_get_devdata(sdev->controller);
	u8 bits_per_word = t->bits_per_word;
	u32 val, mode = 0;

	ss->len = t->len;
	ss->tx_buf = t->tx_buf;
	ss->rx_buf = t->rx_buf;

	ss->hw_mode = sdev->mode;
	sprd_spi_init_hw(ss, t);

	/* Set tansfer speed and valid bits */
	sprd_spi_set_speed(ss, t->speed_hz);
	sprd_spi_set_transfer_bits(ss, bits_per_word);

	if (bits_per_word > 16)
		bits_per_word = round_up(bits_per_word, 16);
	else
		bits_per_word = round_up(bits_per_word, 8);

	switch (bits_per_word) {
	case 8:
		ss->trans_len = t->len;
		ss->read_bufs = sprd_spi_read_bufs_u8;
		ss->write_bufs = sprd_spi_write_bufs_u8;
		ss->dma.width = DMA_SLAVE_BUSWIDTH_1_BYTE;
		ss->dma.fragmens_len = SPRD_SPI_DMA_STEP;
		break;
	case 16:
		ss->trans_len = t->len >> 1;
		ss->read_bufs = sprd_spi_read_bufs_u16;
		ss->write_bufs = sprd_spi_write_bufs_u16;
		ss->dma.width = DMA_SLAVE_BUSWIDTH_2_BYTES;
		ss->dma.fragmens_len = SPRD_SPI_DMA_STEP << 1;
		break;
	case 32:
		ss->trans_len = t->len >> 2;
		ss->read_bufs = sprd_spi_read_bufs_u32;
		ss->write_bufs = sprd_spi_write_bufs_u32;
		ss->dma.width = DMA_SLAVE_BUSWIDTH_4_BYTES;
		ss->dma.fragmens_len = SPRD_SPI_DMA_STEP << 2;
		break;
	default:
		return -EINVAL;
	}

	/* Set transfer read or write mode */
	val = readl_relaxed(ss->base + SPRD_SPI_CTL1);
	val &= ~SPRD_SPI_RTX_MD_MASK;
	if (t->tx_buf)
		mode |= SPRD_SPI_TX_MODE;
	if (t->rx_buf)
		mode |= SPRD_SPI_RX_MODE;

	writel_relaxed(val | mode, ss->base + SPRD_SPI_CTL1);

	ss->trans_mode = mode;

	/*
	 * If in only receive mode, we need to trigger the SPI controller to
	 * receive data automatically.
	 */
	if (ss->trans_mode == SPRD_SPI_RX_MODE)
		ss->write_bufs = sprd_spi_write_only_receive;

	return 0;
}