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
typedef  scalar_t__ u32 ;
struct stm32_qspi_flash {int /*<<< orphan*/  read_mode; struct stm32_qspi* qspi; } ;
struct stm32_qspi_cmd {int tx_data; size_t len; int /*<<< orphan*/  qspimode; int /*<<< orphan*/ * buf; int /*<<< orphan*/  dummy; scalar_t__ addr; int /*<<< orphan*/  addr_width; int /*<<< orphan*/  opcode; } ;
struct stm32_qspi {int /*<<< orphan*/  dev; } ;
struct spi_nor {int /*<<< orphan*/  read_dummy; int /*<<< orphan*/  addr_width; int /*<<< orphan*/  read_opcode; struct stm32_qspi_flash* priv; } ;
typedef  int ssize_t ;
typedef  scalar_t__ loff_t ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,size_t) ; 
 int /*<<< orphan*/  memset (struct stm32_qspi_cmd*,int /*<<< orphan*/ ,int) ; 
 int stm32_qspi_send (struct stm32_qspi_flash*,struct stm32_qspi_cmd*) ; 
 int /*<<< orphan*/  stm32_qspi_set_framemode (struct spi_nor*,struct stm32_qspi_cmd*,int) ; 

__attribute__((used)) static ssize_t stm32_qspi_read(struct spi_nor *nor, loff_t from, size_t len,
			       u_char *buf)
{
	struct stm32_qspi_flash *flash = nor->priv;
	struct stm32_qspi *qspi = flash->qspi;
	struct stm32_qspi_cmd cmd;
	int err;

	dev_dbg(qspi->dev, "read(%#.2x): buf:%pK from:%#.8x len:%#zx\n",
		nor->read_opcode, buf, (u32)from, len);

	memset(&cmd, 0, sizeof(cmd));
	cmd.opcode = nor->read_opcode;
	cmd.addr_width = nor->addr_width;
	cmd.addr = (u32)from;
	cmd.tx_data = true;
	cmd.dummy = nor->read_dummy;
	cmd.len = len;
	cmd.buf = buf;
	cmd.qspimode = flash->read_mode;

	stm32_qspi_set_framemode(nor, &cmd, true);
	err = stm32_qspi_send(flash, &cmd);

	return err ? err : len;
}