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
typedef  scalar_t__ u32 ;
struct spi_nor {int /*<<< orphan*/  reg_proto; int /*<<< orphan*/  erase_opcode; int /*<<< orphan*/  addr_width; struct atmel_qspi* priv; } ;
struct TYPE_4__ {int instruction; int /*<<< orphan*/  address; } ;
struct TYPE_3__ {TYPE_2__ bits; } ;
struct atmel_qspi_command {scalar_t__ address; int /*<<< orphan*/  instruction; TYPE_1__ enable; } ;
struct atmel_qspi {int dummy; } ;
typedef  scalar_t__ loff_t ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int /*<<< orphan*/  QSPI_IFR_TFRTYP_TRSFR_WRITE ; 
 int atmel_qspi_run_command (struct atmel_qspi*,struct atmel_qspi_command*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct atmel_qspi_command*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int atmel_qspi_erase(struct spi_nor *nor, loff_t offs)
{
	struct atmel_qspi *aq = nor->priv;
	struct atmel_qspi_command cmd;

	memset(&cmd, 0, sizeof(cmd));
	cmd.enable.bits.instruction = 1;
	cmd.enable.bits.address = nor->addr_width;
	cmd.instruction = nor->erase_opcode;
	cmd.address = (u32)offs;
	return atmel_qspi_run_command(aq, &cmd, QSPI_IFR_TFRTYP_TRSFR_WRITE,
				      nor->reg_proto);
}