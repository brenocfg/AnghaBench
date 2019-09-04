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
typedef  int /*<<< orphan*/  u8 ;
struct stm32_qspi_flash {TYPE_1__* qspi; } ;
struct stm32_qspi_cmd {int tx_data; int len; int /*<<< orphan*/  qspimode; int /*<<< orphan*/ * buf; int /*<<< orphan*/  opcode; } ;
struct spi_nor {struct stm32_qspi_flash* priv; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  cmd ;
struct TYPE_2__ {struct device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCR_FMODE_INDR ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (struct stm32_qspi_cmd*,int /*<<< orphan*/ ,int) ; 
 int stm32_qspi_send (struct stm32_qspi_flash*,struct stm32_qspi_cmd*) ; 
 int /*<<< orphan*/  stm32_qspi_set_framemode (struct spi_nor*,struct stm32_qspi_cmd*,int) ; 

__attribute__((used)) static int stm32_qspi_read_reg(struct spi_nor *nor,
			       u8 opcode, u8 *buf, int len)
{
	struct stm32_qspi_flash *flash = nor->priv;
	struct device *dev = flash->qspi->dev;
	struct stm32_qspi_cmd cmd;

	dev_dbg(dev, "read_reg: cmd:%#.2x buf:%pK len:%#x\n", opcode, buf, len);

	memset(&cmd, 0, sizeof(cmd));
	cmd.opcode = opcode;
	cmd.tx_data = true;
	cmd.len = len;
	cmd.buf = buf;
	cmd.qspimode = CCR_FMODE_INDR;

	stm32_qspi_set_framemode(nor, &cmd, false);

	return stm32_qspi_send(flash, &cmd);
}