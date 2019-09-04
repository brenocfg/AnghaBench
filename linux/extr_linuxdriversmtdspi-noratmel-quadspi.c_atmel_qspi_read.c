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
typedef  void* u8 ;
typedef  scalar_t__ u32 ;
struct spi_nor {int read_dummy; int /*<<< orphan*/  read_proto; int /*<<< orphan*/  read_opcode; int /*<<< orphan*/  addr_width; struct atmel_qspi* priv; } ;
struct TYPE_3__ {int instruction; int mode; int dummy; int data; int /*<<< orphan*/  address; } ;
struct TYPE_4__ {TYPE_1__ bits; } ;
struct atmel_qspi_command {int mode; size_t buf_len; int /*<<< orphan*/ * rx_buf; void* num_dummy_cycles; void* num_mode_cycles; scalar_t__ address; int /*<<< orphan*/  instruction; TYPE_2__ enable; } ;
struct atmel_qspi {int dummy; } ;
typedef  scalar_t__ ssize_t ;
typedef  scalar_t__ loff_t ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int /*<<< orphan*/  QSPI_IFR_TFRTYP_TRSFR_READ_MEM ; 
 scalar_t__ atmel_qspi_run_command (struct atmel_qspi*,struct atmel_qspi_command*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct atmel_qspi_command*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static ssize_t atmel_qspi_read(struct spi_nor *nor, loff_t from, size_t len,
			       u_char *read_buf)
{
	struct atmel_qspi *aq = nor->priv;
	struct atmel_qspi_command cmd;
	u8 num_mode_cycles, num_dummy_cycles;
	ssize_t ret;

	if (nor->read_dummy >= 2) {
		num_mode_cycles = 2;
		num_dummy_cycles = nor->read_dummy - 2;
	} else {
		num_mode_cycles = nor->read_dummy;
		num_dummy_cycles = 0;
	}

	memset(&cmd, 0, sizeof(cmd));
	cmd.enable.bits.instruction = 1;
	cmd.enable.bits.address = nor->addr_width;
	cmd.enable.bits.mode = (num_mode_cycles > 0);
	cmd.enable.bits.dummy = (num_dummy_cycles > 0);
	cmd.enable.bits.data = 1;
	cmd.instruction = nor->read_opcode;
	cmd.address = (u32)from;
	cmd.mode = 0xff; /* This value prevents from entering the 0-4-4 mode */
	cmd.num_mode_cycles = num_mode_cycles;
	cmd.num_dummy_cycles = num_dummy_cycles;
	cmd.rx_buf = read_buf;
	cmd.buf_len = len;
	ret = atmel_qspi_run_command(aq, &cmd, QSPI_IFR_TFRTYP_TRSFR_READ_MEM,
				     nor->read_proto);
	return (ret < 0) ? ret : len;
}