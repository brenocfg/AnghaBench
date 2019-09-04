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
typedef  int /*<<< orphan*/  u8 ;
struct spi_nor {struct aspeed_smc_chip* priv; } ;
struct aspeed_smc_chip {int /*<<< orphan*/  ahb_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  aspeed_smc_start_user (struct spi_nor*) ; 
 int /*<<< orphan*/  aspeed_smc_stop_user (struct spi_nor*) ; 
 int /*<<< orphan*/  aspeed_smc_write_to_ahb (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int aspeed_smc_write_reg(struct spi_nor *nor, u8 opcode, u8 *buf,
				int len)
{
	struct aspeed_smc_chip *chip = nor->priv;

	aspeed_smc_start_user(nor);
	aspeed_smc_write_to_ahb(chip->ahb_base, &opcode, 1);
	aspeed_smc_write_to_ahb(chip->ahb_base, buf, len);
	aspeed_smc_stop_user(nor);
	return 0;
}