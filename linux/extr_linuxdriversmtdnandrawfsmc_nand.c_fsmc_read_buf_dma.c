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
typedef  int /*<<< orphan*/  uint8_t ;
struct mtd_info {int dummy; } ;
struct fsmc_nand_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  dma_xfer (struct fsmc_nand_data*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 struct fsmc_nand_data* mtd_to_fsmc (struct mtd_info*) ; 

__attribute__((used)) static void fsmc_read_buf_dma(struct mtd_info *mtd, uint8_t *buf, int len)
{
	struct fsmc_nand_data *host  = mtd_to_fsmc(mtd);

	dma_xfer(host, buf, len, DMA_FROM_DEVICE);
}