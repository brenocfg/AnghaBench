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
struct mmp_tdma_chan {scalar_t__ dir; scalar_t__ type; int burst_sz; int buswidth; scalar_t__ reg_base; int /*<<< orphan*/  dev; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 scalar_t__ DMA_DEV_TO_MEM ; 
 scalar_t__ DMA_MEM_TO_DEV ; 
#define  DMA_SLAVE_BUSWIDTH_1_BYTE 130 
#define  DMA_SLAVE_BUSWIDTH_2_BYTES 129 
#define  DMA_SLAVE_BUSWIDTH_4_BYTES 128 
 int EINVAL ; 
 scalar_t__ MMP_AUD_TDMA ; 
 scalar_t__ PXA910_SQU ; 
 scalar_t__ TDCR ; 
 unsigned int TDCR_BURSTSZ_128B ; 
 unsigned int TDCR_BURSTSZ_16B ; 
 unsigned int TDCR_BURSTSZ_32B ; 
 unsigned int TDCR_BURSTSZ_4B ; 
 unsigned int TDCR_BURSTSZ_64B ; 
 unsigned int TDCR_BURSTSZ_8B ; 
 unsigned int TDCR_BURSTSZ_SQU_16B ; 
 unsigned int TDCR_BURSTSZ_SQU_1B ; 
 unsigned int TDCR_BURSTSZ_SQU_2B ; 
 unsigned int TDCR_BURSTSZ_SQU_32B ; 
 unsigned int TDCR_BURSTSZ_SQU_4B ; 
 unsigned int TDCR_BURSTSZ_SQU_8B ; 
 unsigned int TDCR_DSTDIR_ADDR_HOLD ; 
 unsigned int TDCR_DSTDIR_ADDR_INC ; 
 unsigned int TDCR_PACKMOD ; 
 unsigned int TDCR_SRCDIR_ADDR_HOLD ; 
 unsigned int TDCR_SRCDIR_ADDR_INC ; 
 unsigned int TDCR_SSPMOD ; 
 unsigned int TDCR_SSZ_16_BITS ; 
 unsigned int TDCR_SSZ_32_BITS ; 
 unsigned int TDCR_SSZ_8_BITS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mmp_tdma_disable_chan (struct dma_chan*) ; 
 struct mmp_tdma_chan* to_mmp_tdma_chan (struct dma_chan*) ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 

__attribute__((used)) static int mmp_tdma_config_chan(struct dma_chan *chan)
{
	struct mmp_tdma_chan *tdmac = to_mmp_tdma_chan(chan);
	unsigned int tdcr = 0;

	mmp_tdma_disable_chan(chan);

	if (tdmac->dir == DMA_MEM_TO_DEV)
		tdcr = TDCR_DSTDIR_ADDR_HOLD | TDCR_SRCDIR_ADDR_INC;
	else if (tdmac->dir == DMA_DEV_TO_MEM)
		tdcr = TDCR_SRCDIR_ADDR_HOLD | TDCR_DSTDIR_ADDR_INC;

	if (tdmac->type == MMP_AUD_TDMA) {
		tdcr |= TDCR_PACKMOD;

		switch (tdmac->burst_sz) {
		case 4:
			tdcr |= TDCR_BURSTSZ_4B;
			break;
		case 8:
			tdcr |= TDCR_BURSTSZ_8B;
			break;
		case 16:
			tdcr |= TDCR_BURSTSZ_16B;
			break;
		case 32:
			tdcr |= TDCR_BURSTSZ_32B;
			break;
		case 64:
			tdcr |= TDCR_BURSTSZ_64B;
			break;
		case 128:
			tdcr |= TDCR_BURSTSZ_128B;
			break;
		default:
			dev_err(tdmac->dev, "mmp_tdma: unknown burst size.\n");
			return -EINVAL;
		}

		switch (tdmac->buswidth) {
		case DMA_SLAVE_BUSWIDTH_1_BYTE:
			tdcr |= TDCR_SSZ_8_BITS;
			break;
		case DMA_SLAVE_BUSWIDTH_2_BYTES:
			tdcr |= TDCR_SSZ_16_BITS;
			break;
		case DMA_SLAVE_BUSWIDTH_4_BYTES:
			tdcr |= TDCR_SSZ_32_BITS;
			break;
		default:
			dev_err(tdmac->dev, "mmp_tdma: unknown bus size.\n");
			return -EINVAL;
		}
	} else if (tdmac->type == PXA910_SQU) {
		tdcr |= TDCR_SSPMOD;

		switch (tdmac->burst_sz) {
		case 1:
			tdcr |= TDCR_BURSTSZ_SQU_1B;
			break;
		case 2:
			tdcr |= TDCR_BURSTSZ_SQU_2B;
			break;
		case 4:
			tdcr |= TDCR_BURSTSZ_SQU_4B;
			break;
		case 8:
			tdcr |= TDCR_BURSTSZ_SQU_8B;
			break;
		case 16:
			tdcr |= TDCR_BURSTSZ_SQU_16B;
			break;
		case 32:
			tdcr |= TDCR_BURSTSZ_SQU_32B;
			break;
		default:
			dev_err(tdmac->dev, "mmp_tdma: unknown burst size.\n");
			return -EINVAL;
		}
	}

	writel(tdcr, tdmac->reg_base + TDCR);
	return 0;
}