#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_11__ {scalar_t__ dir; scalar_t__ nbytes; } ;
struct TYPE_10__ {int buswidth; int nbytes; int val; } ;
struct TYPE_8__ {int opcode; } ;
struct TYPE_7__ {int buswidth; int nbytes; } ;
struct spi_mem_op {TYPE_5__ data; TYPE_4__ addr; TYPE_2__ cmd; TYPE_1__ dummy; } ;
struct atmel_qspi {scalar_t__ mr; scalar_t__ regs; TYPE_3__* caps; } ;
struct TYPE_12__ {int config; } ;
struct TYPE_9__ {scalar_t__ has_ricr; } ;

/* Variables and functions */
 int ENOTSUPP ; 
 scalar_t__ QSPI_IAR ; 
 scalar_t__ QSPI_ICR ; 
 int QSPI_ICR_INST (int) ; 
 int QSPI_ICR_OPT (int) ; 
 scalar_t__ QSPI_IFR ; 
 int QSPI_IFR_ADDREN ; 
 int QSPI_IFR_ADDRL ; 
 int QSPI_IFR_APBTFRTYP_READ ; 
 int QSPI_IFR_DATAEN ; 
 int QSPI_IFR_INSTEN ; 
 int QSPI_IFR_NBDUM (int) ; 
 int QSPI_IFR_OPTEN ; 
 int QSPI_IFR_OPTL_8BIT ; 
 int QSPI_IFR_SAMA5D2_WRITE_TRSFR ; 
 scalar_t__ QSPI_MR ; 
 scalar_t__ QSPI_MR_SMM ; 
 scalar_t__ QSPI_RICR ; 
 scalar_t__ QSPI_SR ; 
 scalar_t__ QSPI_WICR ; 
 scalar_t__ SPI_MEM_DATA_IN ; 
 scalar_t__ SPI_MEM_DATA_OUT ; 
 int atmel_qspi_find_mode (struct spi_mem_op const*) ; 
 TYPE_6__* atmel_qspi_modes ; 
 int /*<<< orphan*/  readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static int atmel_qspi_set_cfg(struct atmel_qspi *aq,
			      const struct spi_mem_op *op, u32 *offset)
{
	u32 iar, icr, ifr;
	u32 dummy_cycles = 0;
	int mode;

	iar = 0;
	icr = QSPI_ICR_INST(op->cmd.opcode);
	ifr = QSPI_IFR_INSTEN;

	mode = atmel_qspi_find_mode(op);
	if (mode < 0)
		return mode;
	ifr |= atmel_qspi_modes[mode].config;

	if (op->dummy.buswidth && op->dummy.nbytes)
		dummy_cycles = op->dummy.nbytes * 8 / op->dummy.buswidth;

	/*
	 * The controller allows 24 and 32-bit addressing while NAND-flash
	 * requires 16-bit long. Handling 8-bit long addresses is done using
	 * the option field. For the 16-bit addresses, the workaround depends
	 * of the number of requested dummy bits. If there are 8 or more dummy
	 * cycles, the address is shifted and sent with the first dummy byte.
	 * Otherwise opcode is disabled and the first byte of the address
	 * contains the command opcode (works only if the opcode and address
	 * use the same buswidth). The limitation is when the 16-bit address is
	 * used without enough dummy cycles and the opcode is using a different
	 * buswidth than the address.
	 */
	if (op->addr.buswidth) {
		switch (op->addr.nbytes) {
		case 0:
			break;
		case 1:
			ifr |= QSPI_IFR_OPTEN | QSPI_IFR_OPTL_8BIT;
			icr |= QSPI_ICR_OPT(op->addr.val & 0xff);
			break;
		case 2:
			if (dummy_cycles < 8 / op->addr.buswidth) {
				ifr &= ~QSPI_IFR_INSTEN;
				ifr |= QSPI_IFR_ADDREN;
				iar = (op->cmd.opcode << 16) |
					(op->addr.val & 0xffff);
			} else {
				ifr |= QSPI_IFR_ADDREN;
				iar = (op->addr.val << 8) & 0xffffff;
				dummy_cycles -= 8 / op->addr.buswidth;
			}
			break;
		case 3:
			ifr |= QSPI_IFR_ADDREN;
			iar = op->addr.val & 0xffffff;
			break;
		case 4:
			ifr |= QSPI_IFR_ADDREN | QSPI_IFR_ADDRL;
			iar = op->addr.val & 0x7ffffff;
			break;
		default:
			return -ENOTSUPP;
		}
	}

	/* offset of the data access in the QSPI memory space */
	*offset = iar;

	/* Set number of dummy cycles */
	if (dummy_cycles)
		ifr |= QSPI_IFR_NBDUM(dummy_cycles);

	/* Set data enable */
	if (op->data.nbytes)
		ifr |= QSPI_IFR_DATAEN;

	/*
	 * If the QSPI controller is set in regular SPI mode, set it in
	 * Serial Memory Mode (SMM).
	 */
	if (aq->mr != QSPI_MR_SMM) {
		writel_relaxed(QSPI_MR_SMM, aq->regs + QSPI_MR);
		aq->mr = QSPI_MR_SMM;
	}

	/* Clear pending interrupts */
	(void)readl_relaxed(aq->regs + QSPI_SR);

	if (aq->caps->has_ricr) {
		if (!op->addr.nbytes && op->data.dir == SPI_MEM_DATA_IN)
			ifr |= QSPI_IFR_APBTFRTYP_READ;

		/* Set QSPI Instruction Frame registers */
		writel_relaxed(iar, aq->regs + QSPI_IAR);
		if (op->data.dir == SPI_MEM_DATA_IN)
			writel_relaxed(icr, aq->regs + QSPI_RICR);
		else
			writel_relaxed(icr, aq->regs + QSPI_WICR);
		writel_relaxed(ifr, aq->regs + QSPI_IFR);
	} else {
		if (op->data.dir == SPI_MEM_DATA_OUT)
			ifr |= QSPI_IFR_SAMA5D2_WRITE_TRSFR;

		/* Set QSPI Instruction Frame registers */
		writel_relaxed(iar, aq->regs + QSPI_IAR);
		writel_relaxed(icr, aq->regs + QSPI_ICR);
		writel_relaxed(ifr, aq->regs + QSPI_IFR);
	}

	return 0;
}