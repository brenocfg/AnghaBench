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
typedef  int /*<<< orphan*/  u8 ;
struct spi_nor {int /*<<< orphan*/  reg_proto; struct atmel_qspi* priv; } ;
struct TYPE_4__ {int instruction; int data; } ;
struct TYPE_3__ {TYPE_2__ bits; } ;
struct atmel_qspi_command {int buf_len; int /*<<< orphan*/ * rx_buf; int /*<<< orphan*/  instruction; TYPE_1__ enable; } ;
struct atmel_qspi {int dummy; } ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int /*<<< orphan*/  QSPI_IFR_TFRTYP_TRSFR_READ ; 
 int atmel_qspi_run_command (struct atmel_qspi*,struct atmel_qspi_command*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct atmel_qspi_command*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int atmel_qspi_read_reg(struct spi_nor *nor, u8 opcode,
			       u8 *buf, int len)
{
	struct atmel_qspi *aq = nor->priv;
	struct atmel_qspi_command cmd;

	memset(&cmd, 0, sizeof(cmd));
	cmd.enable.bits.instruction = 1;
	cmd.enable.bits.data = 1;
	cmd.instruction = opcode;
	cmd.rx_buf = buf;
	cmd.buf_len = len;
	return atmel_qspi_run_command(aq, &cmd, QSPI_IFR_TFRTYP_TRSFR_READ,
				      nor->reg_proto);
}