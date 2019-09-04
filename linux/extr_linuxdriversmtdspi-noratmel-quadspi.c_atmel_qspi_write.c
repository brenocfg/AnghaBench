#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
typedef  scalar_t__ u32 ;
struct spi_nor {int /*<<< orphan*/  write_proto; int /*<<< orphan*/  program_opcode; int /*<<< orphan*/  addr_width; struct atmel_qspi* priv; } ;
struct TYPE_3__ {int instruction; int data; int /*<<< orphan*/  address; } ;
struct TYPE_4__ {TYPE_1__ bits; } ;
struct atmel_qspi_command {size_t buf_len; int /*<<< orphan*/  const* tx_buf; scalar_t__ address; int /*<<< orphan*/  instruction; TYPE_2__ enable; } ;
struct atmel_qspi {int dummy; } ;
typedef  scalar_t__ ssize_t ;
typedef  scalar_t__ loff_t ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int /*<<< orphan*/  QSPI_IFR_TFRTYP_TRSFR_WRITE_MEM ; 
 scalar_t__ atmel_qspi_run_command (struct atmel_qspi*,struct atmel_qspi_command*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct atmel_qspi_command*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static ssize_t atmel_qspi_write(struct spi_nor *nor, loff_t to, size_t len,
				const u_char *write_buf)
{
	struct atmel_qspi *aq = nor->priv;
	struct atmel_qspi_command cmd;
	ssize_t ret;

	memset(&cmd, 0, sizeof(cmd));
	cmd.enable.bits.instruction = 1;
	cmd.enable.bits.address = nor->addr_width;
	cmd.enable.bits.data = 1;
	cmd.instruction = nor->program_opcode;
	cmd.address = (u32)to;
	cmd.tx_buf = write_buf;
	cmd.buf_len = len;
	ret = atmel_qspi_run_command(aq, &cmd, QSPI_IFR_TFRTYP_TRSFR_WRITE_MEM,
				     nor->write_proto);
	return (ret < 0) ? ret : len;
}