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
struct spi_nor {int /*<<< orphan*/  program_opcode; struct aspeed_smc_chip* priv; } ;
struct aspeed_smc_chip {int /*<<< orphan*/  ahb_base; } ;
typedef  size_t ssize_t ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  aspeed_smc_send_cmd_addr (struct spi_nor*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aspeed_smc_start_user (struct spi_nor*) ; 
 int /*<<< orphan*/  aspeed_smc_stop_user (struct spi_nor*) ; 
 int /*<<< orphan*/  aspeed_smc_write_to_ahb (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,size_t) ; 

__attribute__((used)) static ssize_t aspeed_smc_write_user(struct spi_nor *nor, loff_t to,
				     size_t len, const u_char *write_buf)
{
	struct aspeed_smc_chip *chip = nor->priv;

	aspeed_smc_start_user(nor);
	aspeed_smc_send_cmd_addr(nor, nor->program_opcode, to);
	aspeed_smc_write_to_ahb(chip->ahb_base, write_buf, len);
	aspeed_smc_stop_user(nor);
	return len;
}