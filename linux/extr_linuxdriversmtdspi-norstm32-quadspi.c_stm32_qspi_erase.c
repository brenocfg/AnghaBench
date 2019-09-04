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
typedef  scalar_t__ u32 ;
struct stm32_qspi_flash {TYPE_1__* qspi; } ;
struct stm32_qspi_cmd {int /*<<< orphan*/  qspimode; scalar_t__ addr; int /*<<< orphan*/  addr_width; int /*<<< orphan*/  opcode; } ;
struct spi_nor {int /*<<< orphan*/  addr_width; int /*<<< orphan*/  erase_opcode; struct stm32_qspi_flash* priv; } ;
struct device {int dummy; } ;
typedef  scalar_t__ loff_t ;
typedef  int /*<<< orphan*/  cmd ;
struct TYPE_2__ {struct device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCR_FMODE_INDW ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  memset (struct stm32_qspi_cmd*,int /*<<< orphan*/ ,int) ; 
 int stm32_qspi_send (struct stm32_qspi_flash*,struct stm32_qspi_cmd*) ; 
 int /*<<< orphan*/  stm32_qspi_set_framemode (struct spi_nor*,struct stm32_qspi_cmd*,int) ; 

__attribute__((used)) static int stm32_qspi_erase(struct spi_nor *nor, loff_t offs)
{
	struct stm32_qspi_flash *flash = nor->priv;
	struct device *dev = flash->qspi->dev;
	struct stm32_qspi_cmd cmd;

	dev_dbg(dev, "erase(%#.2x):offs:%#x\n", nor->erase_opcode, (u32)offs);

	memset(&cmd, 0, sizeof(cmd));
	cmd.opcode = nor->erase_opcode;
	cmd.addr_width = nor->addr_width;
	cmd.addr = (u32)offs;
	cmd.qspimode = CCR_FMODE_INDW;

	stm32_qspi_set_framemode(nor, &cmd, false);

	return stm32_qspi_send(flash, &cmd);
}