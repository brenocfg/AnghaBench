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
typedef  int /*<<< orphan*/  u32 ;
struct mpc8xxx_spi {int flags; TYPE_1__* pram; void* dma_dummy_tx; TYPE_1__* rx_bd; TYPE_1__* tx_bd; void* dma_dummy_rx; int /*<<< orphan*/  subblock; struct device* dev; } ;
struct device_node {int dummy; } ;
struct device {struct device_node* of_node; } ;
struct TYPE_2__ {int /*<<< orphan*/  txtmp; int /*<<< orphan*/  tbc; int /*<<< orphan*/  tbptr; int /*<<< orphan*/  tdp; int /*<<< orphan*/  tstate; int /*<<< orphan*/  rxtmp; int /*<<< orphan*/  rbc; int /*<<< orphan*/  rbptr; int /*<<< orphan*/  rdp; int /*<<< orphan*/  rstate; int /*<<< orphan*/  mrblr; int /*<<< orphan*/  rfcr; int /*<<< orphan*/  tfcr; int /*<<< orphan*/  rbase; int /*<<< orphan*/  tbase; } ;

/* Variables and functions */
 int CPMFCR_EB ; 
 int CPMFCR_GBL ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int ENOMEM ; 
 scalar_t__ IS_ERR (void*) ; 
 scalar_t__ IS_ERR_VALUE (unsigned long) ; 
 unsigned long PAGE_SIZE ; 
 int /*<<< orphan*/  QE_CR_SUBBLOCK_SPI1 ; 
 int /*<<< orphan*/  QE_CR_SUBBLOCK_SPI2 ; 
 int SPI_CPM1 ; 
 int SPI_CPM_MODE ; 
 unsigned long SPI_MRBLR ; 
 int SPI_QE ; 
 void* cpm_muram_addr (unsigned long) ; 
 unsigned long cpm_muram_alloc (int,int) ; 
 int /*<<< orphan*/  cpm_muram_free (unsigned long) ; 
 unsigned long cpm_muram_offset (TYPE_1__*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*) ; 
 void* devm_platform_ioremap_resource (int /*<<< orphan*/ ,int) ; 
 void* dma_map_single (struct device*,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (struct device*,void*) ; 
 int /*<<< orphan*/  dma_unmap_single (struct device*,void*,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  empty_zero_page ; 
 int /*<<< orphan*/  fsl_dummy_rx ; 
 int /*<<< orphan*/  fsl_spi_alloc_dummy_rx () ; 
 unsigned long fsl_spi_cpm_get_pram (struct mpc8xxx_spi*) ; 
 int /*<<< orphan*/  fsl_spi_free_dummy_rx () ; 
 int /*<<< orphan*/ * of_get_property (struct device_node*,char*,int*) ; 
 int /*<<< orphan*/  out_8 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  out_be16 (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  out_be32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_platform_device (struct device*) ; 

int fsl_spi_cpm_init(struct mpc8xxx_spi *mspi)
{
	struct device *dev = mspi->dev;
	struct device_node *np = dev->of_node;
	const u32 *iprop;
	int size;
	unsigned long bds_ofs;

	if (!(mspi->flags & SPI_CPM_MODE))
		return 0;

	if (!fsl_spi_alloc_dummy_rx())
		return -ENOMEM;

	if (mspi->flags & SPI_QE) {
		iprop = of_get_property(np, "cell-index", &size);
		if (iprop && size == sizeof(*iprop))
			mspi->subblock = *iprop;

		switch (mspi->subblock) {
		default:
			dev_warn(dev, "cell-index unspecified, assuming SPI1\n");
			/* fall through */
		case 0:
			mspi->subblock = QE_CR_SUBBLOCK_SPI1;
			break;
		case 1:
			mspi->subblock = QE_CR_SUBBLOCK_SPI2;
			break;
		}
	}

	if (mspi->flags & SPI_CPM1) {
		void *pram;

		pram = devm_platform_ioremap_resource(to_platform_device(dev),
						      1);
		if (IS_ERR(pram))
			mspi->pram = NULL;
		else
			mspi->pram = pram;
	} else {
		unsigned long pram_ofs = fsl_spi_cpm_get_pram(mspi);

		if (IS_ERR_VALUE(pram_ofs))
			mspi->pram = NULL;
		else
			mspi->pram = cpm_muram_addr(pram_ofs);
	}
	if (mspi->pram == NULL) {
		dev_err(dev, "can't allocate spi parameter ram\n");
		goto err_pram;
	}

	bds_ofs = cpm_muram_alloc(sizeof(*mspi->tx_bd) +
				  sizeof(*mspi->rx_bd), 8);
	if (IS_ERR_VALUE(bds_ofs)) {
		dev_err(dev, "can't allocate bds\n");
		goto err_bds;
	}

	mspi->dma_dummy_tx = dma_map_single(dev, empty_zero_page, PAGE_SIZE,
					    DMA_TO_DEVICE);
	if (dma_mapping_error(dev, mspi->dma_dummy_tx)) {
		dev_err(dev, "unable to map dummy tx buffer\n");
		goto err_dummy_tx;
	}

	mspi->dma_dummy_rx = dma_map_single(dev, fsl_dummy_rx, SPI_MRBLR,
					    DMA_FROM_DEVICE);
	if (dma_mapping_error(dev, mspi->dma_dummy_rx)) {
		dev_err(dev, "unable to map dummy rx buffer\n");
		goto err_dummy_rx;
	}

	mspi->tx_bd = cpm_muram_addr(bds_ofs);
	mspi->rx_bd = cpm_muram_addr(bds_ofs + sizeof(*mspi->tx_bd));

	/* Initialize parameter ram. */
	out_be16(&mspi->pram->tbase, cpm_muram_offset(mspi->tx_bd));
	out_be16(&mspi->pram->rbase, cpm_muram_offset(mspi->rx_bd));
	out_8(&mspi->pram->tfcr, CPMFCR_EB | CPMFCR_GBL);
	out_8(&mspi->pram->rfcr, CPMFCR_EB | CPMFCR_GBL);
	out_be16(&mspi->pram->mrblr, SPI_MRBLR);
	out_be32(&mspi->pram->rstate, 0);
	out_be32(&mspi->pram->rdp, 0);
	out_be16(&mspi->pram->rbptr, 0);
	out_be16(&mspi->pram->rbc, 0);
	out_be32(&mspi->pram->rxtmp, 0);
	out_be32(&mspi->pram->tstate, 0);
	out_be32(&mspi->pram->tdp, 0);
	out_be16(&mspi->pram->tbptr, 0);
	out_be16(&mspi->pram->tbc, 0);
	out_be32(&mspi->pram->txtmp, 0);

	return 0;

err_dummy_rx:
	dma_unmap_single(dev, mspi->dma_dummy_tx, PAGE_SIZE, DMA_TO_DEVICE);
err_dummy_tx:
	cpm_muram_free(bds_ofs);
err_bds:
	if (!(mspi->flags & SPI_CPM1))
		cpm_muram_free(cpm_muram_offset(mspi->pram));
err_pram:
	fsl_spi_free_dummy_rx();
	return -ENOMEM;
}