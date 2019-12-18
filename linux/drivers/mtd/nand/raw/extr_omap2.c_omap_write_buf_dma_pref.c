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
typedef  int /*<<< orphan*/  u_char ;
struct nand_chip {int dummy; } ;
struct mtd_info {int oobsize; } ;

/* Variables and functions */
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 
 int /*<<< orphan*/  omap_nand_dma_transfer (struct mtd_info*,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  omap_write_buf_pref (struct nand_chip*,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static void omap_write_buf_dma_pref(struct nand_chip *chip, const u_char *buf,
				    int len)
{
	struct mtd_info *mtd = nand_to_mtd(chip);

	if (len <= mtd->oobsize)
		omap_write_buf_pref(chip, buf, len);
	else
		/* start transfer in DMA mode */
		omap_nand_dma_transfer(mtd, (u_char *)buf, len, 0x1);
}