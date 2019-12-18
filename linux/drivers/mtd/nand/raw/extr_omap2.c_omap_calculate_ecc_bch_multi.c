#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_6__ {int /*<<< orphan*/  gpmc_ecc_config; } ;
struct TYPE_4__ {int bytes; } ;
struct TYPE_5__ {TYPE_1__ ecc; } ;
struct omap_nand_info {TYPE_3__ reg; TYPE_2__ nand; } ;
struct mtd_info {int dummy; } ;

/* Variables and functions */
 int _omap_calculate_ecc_bch (struct mtd_info*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int) ; 
 struct omap_nand_info* mtd_to_omap (struct mtd_info*) ; 
 int readl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int omap_calculate_ecc_bch_multi(struct mtd_info *mtd,
					const u_char *dat, u_char *ecc_calc)
{
	struct omap_nand_info *info = mtd_to_omap(mtd);
	int eccbytes = info->nand.ecc.bytes;
	unsigned long nsectors;
	int i, ret;

	nsectors = ((readl(info->reg.gpmc_ecc_config) >> 4) & 0x7) + 1;
	for (i = 0; i < nsectors; i++) {
		ret = _omap_calculate_ecc_bch(mtd, dat, ecc_calc, i);
		if (ret)
			return ret;

		ecc_calc += eccbytes;
	}

	return 0;
}