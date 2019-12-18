#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_8__ {int /*<<< orphan*/  gpmc_ecc_config; int /*<<< orphan*/  gpmc_ecc_control; int /*<<< orphan*/  gpmc_ecc_size_config; } ;
struct TYPE_5__ {int size; } ;
struct TYPE_6__ {TYPE_1__ ecc; } ;
struct omap_nand_info {int gpmc_cs; TYPE_4__ reg; TYPE_3__* pdev; TYPE_2__ nand; } ;
struct nand_chip {int options; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ECC1 ; 
 int ECC1RESULTSIZE ; 
 int ECCCLEAR ; 
 int ECCSIZE1_SHIFT ; 
 int NAND_BUSWIDTH_16 ; 
#define  NAND_ECC_READ 130 
#define  NAND_ECC_READSYN 129 
#define  NAND_ECC_WRITE 128 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int) ; 
 struct omap_nand_info* mtd_to_omap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nand_to_mtd (struct nand_chip*) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void omap_enable_hwecc(struct nand_chip *chip, int mode)
{
	struct omap_nand_info *info = mtd_to_omap(nand_to_mtd(chip));
	unsigned int dev_width = (chip->options & NAND_BUSWIDTH_16) ? 1 : 0;
	u32 val;

	/* clear ecc and enable bits */
	val = ECCCLEAR | ECC1;
	writel(val, info->reg.gpmc_ecc_control);

	/* program ecc and result sizes */
	val = ((((info->nand.ecc.size >> 1) - 1) << ECCSIZE1_SHIFT) |
			 ECC1RESULTSIZE);
	writel(val, info->reg.gpmc_ecc_size_config);

	switch (mode) {
	case NAND_ECC_READ:
	case NAND_ECC_WRITE:
		writel(ECCCLEAR | ECC1, info->reg.gpmc_ecc_control);
		break;
	case NAND_ECC_READSYN:
		writel(ECCCLEAR, info->reg.gpmc_ecc_control);
		break;
	default:
		dev_info(&info->pdev->dev,
			"error: unrecognized Mode[%d]!\n", mode);
		break;
	}

	/* (ECC 16 or 8 bit col) | ( CS  )  | ECC Enable */
	val = (dev_width << 7) | (info->gpmc_cs << 1) | (0x1);
	writel(val, info->reg.gpmc_ecc_config);
}