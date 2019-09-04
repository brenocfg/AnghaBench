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
typedef  scalar_t__ u32 ;
struct stm32_qspi_flash {TYPE_1__* qspi; } ;
struct stm32_qspi_cmd {int tx_data; size_t len; int /*<<< orphan*/  qspimode; void* buf; scalar_t__ addr; int /*<<< orphan*/  addr_width; int /*<<< orphan*/  opcode; } ;
struct spi_nor {int /*<<< orphan*/  addr_width; int /*<<< orphan*/  program_opcode; struct stm32_qspi_flash* priv; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
typedef  scalar_t__ loff_t ;
typedef  int /*<<< orphan*/  cmd ;
struct TYPE_2__ {struct device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCR_FMODE_INDW ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,scalar_t__,size_t) ; 
 int /*<<< orphan*/  memset (struct stm32_qspi_cmd*,int /*<<< orphan*/ ,int) ; 
 int stm32_qspi_send (struct stm32_qspi_flash*,struct stm32_qspi_cmd*) ; 
 int /*<<< orphan*/  stm32_qspi_set_framemode (struct spi_nor*,struct stm32_qspi_cmd*,int) ; 

__attribute__((used)) static ssize_t stm32_qspi_write(struct spi_nor *nor, loff_t to, size_t len,
				const u_char *buf)
{
	struct stm32_qspi_flash *flash = nor->priv;
	struct device *dev = flash->qspi->dev;
	struct stm32_qspi_cmd cmd;
	int err;

	dev_dbg(dev, "write(%#.2x): buf:%p to:%#.8x len:%#zx\n",
		nor->program_opcode, buf, (u32)to, len);

	memset(&cmd, 0, sizeof(cmd));
	cmd.opcode = nor->program_opcode;
	cmd.addr_width = nor->addr_width;
	cmd.addr = (u32)to;
	cmd.tx_data = true;
	cmd.len = len;
	cmd.buf = (void *)buf;
	cmd.qspimode = CCR_FMODE_INDW;

	stm32_qspi_set_framemode(nor, &cmd, false);
	err = stm32_qspi_send(flash, &cmd);

	return err ? err : len;
}