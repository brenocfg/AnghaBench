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
struct spi_nor {int (* write_reg ) (struct spi_nor*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;int /*<<< orphan*/  erase_opcode; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  SPINOR_OP_WREN ; 
 int cqspi_command_write_addr (struct spi_nor*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int cqspi_set_protocol (struct spi_nor*,int /*<<< orphan*/ ) ; 
 int stub1 (struct spi_nor*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cqspi_erase(struct spi_nor *nor, loff_t offs)
{
	int ret;

	ret = cqspi_set_protocol(nor, 0);
	if (ret)
		return ret;

	/* Send write enable, then erase commands. */
	ret = nor->write_reg(nor, SPINOR_OP_WREN, NULL, 0);
	if (ret)
		return ret;

	/* Set up command buffer. */
	ret = cqspi_command_write_addr(nor, nor->erase_opcode, offs);
	if (ret)
		return ret;

	return 0;
}