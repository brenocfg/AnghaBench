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
typedef  int /*<<< orphan*/  u_char ;
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  gpmc_ecc1_result; int /*<<< orphan*/  gpmc_ecc_config; } ;
struct omap_nand_info {int gpmc_cs; TYPE_1__ reg; } ;
struct nand_chip {int dummy; } ;

/* Variables and functions */
 int CS_MASK ; 
 int ECC_CONFIG_CS_SHIFT ; 
 int EINVAL ; 
 struct omap_nand_info* mtd_to_omap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nand_to_mtd (struct nand_chip*) ; 
 int readl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int omap_calculate_ecc(struct nand_chip *chip, const u_char *dat,
			      u_char *ecc_code)
{
	struct omap_nand_info *info = mtd_to_omap(nand_to_mtd(chip));
	u32 val;

	val = readl(info->reg.gpmc_ecc_config);
	if (((val >> ECC_CONFIG_CS_SHIFT) & CS_MASK) != info->gpmc_cs)
		return -EINVAL;

	/* read ecc result */
	val = readl(info->reg.gpmc_ecc1_result);
	*ecc_code++ = val;          /* P128e, ..., P1e */
	*ecc_code++ = val >> 16;    /* P128o, ..., P1o */
	/* P2048o, P1024o, P512o, P256o, P2048e, P1024e, P512e, P256e */
	*ecc_code++ = ((val >> 8) & 0x0f) | ((val >> 20) & 0xf0);

	return 0;
}