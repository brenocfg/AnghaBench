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
typedef  int u32 ;
struct TYPE_3__ {int address; scalar_t__ data; scalar_t__ dummy; scalar_t__ mode; scalar_t__ instruction; } ;
struct TYPE_4__ {TYPE_1__ bits; } ;
struct atmel_qspi_command {int address; int num_mode_cycles; int /*<<< orphan*/  rx_buf; int /*<<< orphan*/  tx_buf; TYPE_2__ enable; int /*<<< orphan*/  num_dummy_cycles; int /*<<< orphan*/  mode; int /*<<< orphan*/  instruction; } ;
struct atmel_qspi {int pending; int /*<<< orphan*/  cmd_completion; } ;
typedef  enum spi_nor_protocol { ____Placeholder_spi_nor_protocol } spi_nor_protocol ;

/* Variables and functions */
 int EINVAL ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  QSPI_CR ; 
 int QSPI_CR_LASTXFER ; 
 int /*<<< orphan*/  QSPI_IAR ; 
 int /*<<< orphan*/  QSPI_ICR ; 
 int QSPI_ICR_INST (int /*<<< orphan*/ ) ; 
 int QSPI_ICR_OPT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QSPI_IDR ; 
 int /*<<< orphan*/  QSPI_IER ; 
 int /*<<< orphan*/  QSPI_IFR ; 
 int QSPI_IFR_ADDREN ; 
 int QSPI_IFR_ADDRL ; 
 int QSPI_IFR_CRM ; 
 int QSPI_IFR_DATAEN ; 
 int QSPI_IFR_INSTEN ; 
 int QSPI_IFR_NBDUM (int /*<<< orphan*/ ) ; 
 int QSPI_IFR_OPTEN ; 
 int QSPI_IFR_OPTL_1BIT ; 
 int QSPI_IFR_OPTL_2BIT ; 
 int QSPI_IFR_OPTL_4BIT ; 
 int QSPI_IFR_OPTL_8BIT ; 
#define  QSPI_IFR_WIDTH_DUAL_CMD 141 
#define  QSPI_IFR_WIDTH_DUAL_IO 140 
#define  QSPI_IFR_WIDTH_DUAL_OUTPUT 139 
 int QSPI_IFR_WIDTH_MASK ; 
#define  QSPI_IFR_WIDTH_QUAD_CMD 138 
#define  QSPI_IFR_WIDTH_QUAD_IO 137 
#define  QSPI_IFR_WIDTH_QUAD_OUTPUT 136 
#define  QSPI_IFR_WIDTH_SINGLE_BIT_SPI 135 
 int /*<<< orphan*/  QSPI_SR ; 
 int QSPI_SR_CMD_COMPLETED ; 
#define  SNOR_PROTO_1_1_1 134 
#define  SNOR_PROTO_1_1_2 133 
#define  SNOR_PROTO_1_1_4 132 
#define  SNOR_PROTO_1_2_2 131 
#define  SNOR_PROTO_1_4_4 130 
#define  SNOR_PROTO_2_2_2 129 
#define  SNOR_PROTO_4_4_4 128 
 int /*<<< orphan*/  atmel_qspi_debug_command (struct atmel_qspi*,struct atmel_qspi_command const*,int) ; 
 int atmel_qspi_run_transfer (struct atmel_qspi*,struct atmel_qspi_command const*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int qspi_readl (struct atmel_qspi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qspi_writel (struct atmel_qspi*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int atmel_qspi_run_command(struct atmel_qspi *aq,
				  const struct atmel_qspi_command *cmd,
				  u32 ifr_tfrtyp, enum spi_nor_protocol proto)
{
	u32 iar, icr, ifr, sr;
	int err = 0;

	iar = 0;
	icr = 0;
	ifr = ifr_tfrtyp;

	/* Set the SPI protocol */
	switch (proto) {
	case SNOR_PROTO_1_1_1:
		ifr |= QSPI_IFR_WIDTH_SINGLE_BIT_SPI;
		break;

	case SNOR_PROTO_1_1_2:
		ifr |= QSPI_IFR_WIDTH_DUAL_OUTPUT;
		break;

	case SNOR_PROTO_1_1_4:
		ifr |= QSPI_IFR_WIDTH_QUAD_OUTPUT;
		break;

	case SNOR_PROTO_1_2_2:
		ifr |= QSPI_IFR_WIDTH_DUAL_IO;
		break;

	case SNOR_PROTO_1_4_4:
		ifr |= QSPI_IFR_WIDTH_QUAD_IO;
		break;

	case SNOR_PROTO_2_2_2:
		ifr |= QSPI_IFR_WIDTH_DUAL_CMD;
		break;

	case SNOR_PROTO_4_4_4:
		ifr |= QSPI_IFR_WIDTH_QUAD_CMD;
		break;

	default:
		return -EINVAL;
	}

	/* Compute instruction parameters */
	if (cmd->enable.bits.instruction) {
		icr |= QSPI_ICR_INST(cmd->instruction);
		ifr |= QSPI_IFR_INSTEN;
	}

	/* Compute address parameters */
	switch (cmd->enable.bits.address) {
	case 4:
		ifr |= QSPI_IFR_ADDRL;
		/* fall through to the 24bit (3 byte) address case. */
	case 3:
		iar = (cmd->enable.bits.data) ? 0 : cmd->address;
		ifr |= QSPI_IFR_ADDREN;
		break;
	case 0:
		break;
	default:
		return -EINVAL;
	}

	/* Compute option parameters */
	if (cmd->enable.bits.mode && cmd->num_mode_cycles) {
		u32 mode_cycle_bits, mode_bits;

		icr |= QSPI_ICR_OPT(cmd->mode);
		ifr |= QSPI_IFR_OPTEN;

		switch (ifr & QSPI_IFR_WIDTH_MASK) {
		case QSPI_IFR_WIDTH_SINGLE_BIT_SPI:
		case QSPI_IFR_WIDTH_DUAL_OUTPUT:
		case QSPI_IFR_WIDTH_QUAD_OUTPUT:
			mode_cycle_bits = 1;
			break;
		case QSPI_IFR_WIDTH_DUAL_IO:
		case QSPI_IFR_WIDTH_DUAL_CMD:
			mode_cycle_bits = 2;
			break;
		case QSPI_IFR_WIDTH_QUAD_IO:
		case QSPI_IFR_WIDTH_QUAD_CMD:
			mode_cycle_bits = 4;
			break;
		default:
			return -EINVAL;
		}

		mode_bits = cmd->num_mode_cycles * mode_cycle_bits;
		switch (mode_bits) {
		case 1:
			ifr |= QSPI_IFR_OPTL_1BIT;
			break;

		case 2:
			ifr |= QSPI_IFR_OPTL_2BIT;
			break;

		case 4:
			ifr |= QSPI_IFR_OPTL_4BIT;
			break;

		case 8:
			ifr |= QSPI_IFR_OPTL_8BIT;
			break;

		default:
			return -EINVAL;
		}
	}

	/* Set number of dummy cycles */
	if (cmd->enable.bits.dummy)
		ifr |= QSPI_IFR_NBDUM(cmd->num_dummy_cycles);

	/* Set data enable */
	if (cmd->enable.bits.data) {
		ifr |= QSPI_IFR_DATAEN;

		/* Special case for Continuous Read Mode */
		if (!cmd->tx_buf && !cmd->rx_buf)
			ifr |= QSPI_IFR_CRM;
	}

	/* Clear pending interrupts */
	(void)qspi_readl(aq, QSPI_SR);

	/* Set QSPI Instruction Frame registers */
	atmel_qspi_debug_command(aq, cmd, ifr);
	qspi_writel(aq, QSPI_IAR, iar);
	qspi_writel(aq, QSPI_ICR, icr);
	qspi_writel(aq, QSPI_IFR, ifr);

	/* Skip to the final steps if there is no data */
	if (!cmd->enable.bits.data)
		goto no_data;

	/* Dummy read of QSPI_IFR to synchronize APB and AHB accesses */
	(void)qspi_readl(aq, QSPI_IFR);

	/* Stop here for continuous read */
	if (!cmd->tx_buf && !cmd->rx_buf)
		return 0;
	/* Send/Receive data */
	err = atmel_qspi_run_transfer(aq, cmd);

	/* Release the chip-select */
	qspi_writel(aq, QSPI_CR, QSPI_CR_LASTXFER);

	if (err)
		return err;

#if defined(DEBUG) && defined(VERBOSE_DEBUG)
	/*
	 * If verbose debug is enabled, also dump the RX data in addition to
	 * the SPI command previously dumped by atmel_qspi_debug_command()
	 */
	if (cmd->rx_buf)
		print_hex_dump(KERN_DEBUG, "qspi rx : ", DUMP_PREFIX_NONE,
			       32, 1, cmd->rx_buf, cmd->buf_len, false);
#endif
no_data:
	/* Poll INSTRuction End status */
	sr = qspi_readl(aq, QSPI_SR);
	if ((sr & QSPI_SR_CMD_COMPLETED) == QSPI_SR_CMD_COMPLETED)
		return err;

	/* Wait for INSTRuction End interrupt */
	reinit_completion(&aq->cmd_completion);
	aq->pending = sr & QSPI_SR_CMD_COMPLETED;
	qspi_writel(aq, QSPI_IER, QSPI_SR_CMD_COMPLETED);
	if (!wait_for_completion_timeout(&aq->cmd_completion,
					 msecs_to_jiffies(1000)))
		err = -ETIMEDOUT;
	qspi_writel(aq, QSPI_IDR, QSPI_SR_CMD_COMPLETED);

	return err;
}