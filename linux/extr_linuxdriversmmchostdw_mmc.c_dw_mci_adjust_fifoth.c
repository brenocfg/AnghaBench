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
struct mmc_data {unsigned int blksz; } ;
struct dw_mci {int data_shift; int fifo_depth; int /*<<< orphan*/  use_dma; } ;

/* Variables and functions */
 int ARRAY_SIZE (int const*) ; 
 int /*<<< orphan*/  FIFOTH ; 
 int SDMMC_SET_FIFOTH (int,int,int) ; 
 int /*<<< orphan*/  mci_writel (struct dw_mci*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void dw_mci_adjust_fifoth(struct dw_mci *host, struct mmc_data *data)
{
	unsigned int blksz = data->blksz;
	static const u32 mszs[] = {1, 4, 8, 16, 32, 64, 128, 256};
	u32 fifo_width = 1 << host->data_shift;
	u32 blksz_depth = blksz / fifo_width, fifoth_val;
	u32 msize = 0, rx_wmark = 1, tx_wmark, tx_wmark_invers;
	int idx = ARRAY_SIZE(mszs) - 1;

	/* pio should ship this scenario */
	if (!host->use_dma)
		return;

	tx_wmark = (host->fifo_depth) / 2;
	tx_wmark_invers = host->fifo_depth - tx_wmark;

	/*
	 * MSIZE is '1',
	 * if blksz is not a multiple of the FIFO width
	 */
	if (blksz % fifo_width)
		goto done;

	do {
		if (!((blksz_depth % mszs[idx]) ||
		     (tx_wmark_invers % mszs[idx]))) {
			msize = idx;
			rx_wmark = mszs[idx] - 1;
			break;
		}
	} while (--idx > 0);
	/*
	 * If idx is '0', it won't be tried
	 * Thus, initial values are uesed
	 */
done:
	fifoth_val = SDMMC_SET_FIFOTH(msize, rx_wmark, tx_wmark);
	mci_writel(host, FIFOTH, fifoth_val);
}