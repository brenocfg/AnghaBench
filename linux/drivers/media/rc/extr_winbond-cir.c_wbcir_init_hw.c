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
struct wbcir_data {int txmask; int txcarrier; scalar_t__ txstate; int /*<<< orphan*/ * txbuf; int /*<<< orphan*/  dev; int /*<<< orphan*/  rxstate; scalar_t__ sbase; scalar_t__ ebase; scalar_t__ wbase; } ;

/* Variables and functions */
 int /*<<< orphan*/  WBCIR_BANK_0 ; 
 int /*<<< orphan*/  WBCIR_BANK_2 ; 
 int /*<<< orphan*/  WBCIR_BANK_4 ; 
 int /*<<< orphan*/  WBCIR_BANK_5 ; 
 int /*<<< orphan*/  WBCIR_BANK_6 ; 
 int /*<<< orphan*/  WBCIR_BANK_7 ; 
 int WBCIR_EXT_ENABLE ; 
 int WBCIR_IRQ_ERR ; 
 int WBCIR_IRQ_NONE ; 
 int WBCIR_IRQ_RX ; 
 int WBCIR_IRTX_INV ; 
 scalar_t__ WBCIR_REG_ECEIR_CCTL ; 
 scalar_t__ WBCIR_REG_ECEIR_CTS ; 
 scalar_t__ WBCIR_REG_SP3_ASCR ; 
 scalar_t__ WBCIR_REG_SP3_BGDH ; 
 scalar_t__ WBCIR_REG_SP3_BGDL ; 
 scalar_t__ WBCIR_REG_SP3_EXCR1 ; 
 scalar_t__ WBCIR_REG_SP3_EXCR2 ; 
 scalar_t__ WBCIR_REG_SP3_FCR ; 
 scalar_t__ WBCIR_REG_SP3_IRCFG4 ; 
 scalar_t__ WBCIR_REG_SP3_IRCR1 ; 
 scalar_t__ WBCIR_REG_SP3_IRCR2 ; 
 scalar_t__ WBCIR_REG_SP3_IRCR3 ; 
 scalar_t__ WBCIR_REG_SP3_IRRXDC ; 
 scalar_t__ WBCIR_REG_SP3_IRTXMC ; 
 scalar_t__ WBCIR_REG_SP3_LSR ; 
 scalar_t__ WBCIR_REG_SP3_MCR ; 
 scalar_t__ WBCIR_REG_SP3_MSR ; 
 scalar_t__ WBCIR_REG_SP3_RCCFG ; 
 scalar_t__ WBCIR_REG_WCEIR_CFG1 ; 
 scalar_t__ WBCIR_REG_WCEIR_CTL ; 
 scalar_t__ WBCIR_REG_WCEIR_EV_EN ; 
 scalar_t__ WBCIR_REG_WCEIR_STS ; 
 int /*<<< orphan*/  WBCIR_RXSTATE_INACTIVE ; 
 scalar_t__ WBCIR_TXSTATE_ACTIVE ; 
 scalar_t__ WBCIR_TXSTATE_INACTIVE ; 
 int /*<<< orphan*/  inb (scalar_t__) ; 
 scalar_t__ invert ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 
 scalar_t__ txandrx ; 
 int /*<<< orphan*/  wbcir_idle_rx (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wbcir_select_bank (struct wbcir_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wbcir_set_bits (scalar_t__,int,int) ; 
 int /*<<< orphan*/  wbcir_set_irqmask (struct wbcir_data*,int) ; 

__attribute__((used)) static void
wbcir_init_hw(struct wbcir_data *data)
{
	/* Disable interrupts */
	wbcir_set_irqmask(data, WBCIR_IRQ_NONE);

	/* Set RX_INV, Clear CEIR_EN (needed for the led) */
	wbcir_set_bits(data->wbase + WBCIR_REG_WCEIR_CTL, invert ? 8 : 0, 0x09);

	/* Clear status bits NEC_REP, BUFF, MSG_END, MATCH */
	wbcir_set_bits(data->wbase + WBCIR_REG_WCEIR_STS, 0x17, 0x17);

	/* Clear BUFF_EN, Clear END_EN, Clear MATCH_EN */
	wbcir_set_bits(data->wbase + WBCIR_REG_WCEIR_EV_EN, 0x00, 0x07);

	/* Set RC5 cell time to correspond to 36 kHz */
	wbcir_set_bits(data->wbase + WBCIR_REG_WCEIR_CFG1, 0x4A, 0x7F);

	/* Set IRTX_INV */
	if (invert)
		outb(WBCIR_IRTX_INV, data->ebase + WBCIR_REG_ECEIR_CCTL);
	else
		outb(0x00, data->ebase + WBCIR_REG_ECEIR_CCTL);

	/*
	 * Clear IR LED, set SP3 clock to 24Mhz, set TX mask to IRTX1,
	 * set SP3_IRRX_SW to binary 01, helpfully not documented
	 */
	outb(0x10, data->ebase + WBCIR_REG_ECEIR_CTS);
	data->txmask = 0x1;

	/* Enable extended mode */
	wbcir_select_bank(data, WBCIR_BANK_2);
	outb(WBCIR_EXT_ENABLE, data->sbase + WBCIR_REG_SP3_EXCR1);

	/*
	 * Configure baud generator, IR data will be sampled at
	 * a bitrate of: (24Mhz * prescaler) / (divisor * 16).
	 *
	 * The ECIR registers include a flag to change the
	 * 24Mhz clock freq to 48Mhz.
	 *
	 * It's not documented in the specs, but fifo levels
	 * other than 16 seems to be unsupported.
	 */

	/* prescaler 1.0, tx/rx fifo lvl 16 */
	outb(0x30, data->sbase + WBCIR_REG_SP3_EXCR2);

	/* Set baud divisor to sample every 10 us */
	outb(0x0f, data->sbase + WBCIR_REG_SP3_BGDL);
	outb(0x00, data->sbase + WBCIR_REG_SP3_BGDH);

	/* Set CEIR mode */
	wbcir_select_bank(data, WBCIR_BANK_0);
	outb(0xC0, data->sbase + WBCIR_REG_SP3_MCR);
	inb(data->sbase + WBCIR_REG_SP3_LSR); /* Clear LSR */
	inb(data->sbase + WBCIR_REG_SP3_MSR); /* Clear MSR */

	/* Disable RX demod, enable run-length enc/dec, set freq span */
	wbcir_select_bank(data, WBCIR_BANK_7);
	outb(0x90, data->sbase + WBCIR_REG_SP3_RCCFG);

	/* Disable timer */
	wbcir_select_bank(data, WBCIR_BANK_4);
	outb(0x00, data->sbase + WBCIR_REG_SP3_IRCR1);

	/* Disable MSR interrupt, clear AUX_IRX, mask RX during TX? */
	wbcir_select_bank(data, WBCIR_BANK_5);
	outb(txandrx ? 0x03 : 0x02, data->sbase + WBCIR_REG_SP3_IRCR2);

	/* Disable CRC */
	wbcir_select_bank(data, WBCIR_BANK_6);
	outb(0x20, data->sbase + WBCIR_REG_SP3_IRCR3);

	/* Set RX demodulation freq, not really used */
	wbcir_select_bank(data, WBCIR_BANK_7);
	outb(0xF2, data->sbase + WBCIR_REG_SP3_IRRXDC);

	/* Set TX modulation, 36kHz, 7us pulse width */
	outb(0x69, data->sbase + WBCIR_REG_SP3_IRTXMC);
	data->txcarrier = 36000;

	/* Set invert and pin direction */
	if (invert)
		outb(0x10, data->sbase + WBCIR_REG_SP3_IRCFG4);
	else
		outb(0x00, data->sbase + WBCIR_REG_SP3_IRCFG4);

	/* Set FIFO thresholds (RX = 8, TX = 3), reset RX/TX */
	wbcir_select_bank(data, WBCIR_BANK_0);
	outb(0x97, data->sbase + WBCIR_REG_SP3_FCR);

	/* Clear AUX status bits */
	outb(0xE0, data->sbase + WBCIR_REG_SP3_ASCR);

	/* Clear RX state */
	data->rxstate = WBCIR_RXSTATE_INACTIVE;
	wbcir_idle_rx(data->dev, true);

	/* Clear TX state */
	if (data->txstate == WBCIR_TXSTATE_ACTIVE) {
		kfree(data->txbuf);
		data->txbuf = NULL;
		data->txstate = WBCIR_TXSTATE_INACTIVE;
	}

	/* Enable interrupts */
	wbcir_set_irqmask(data, WBCIR_IRQ_RX | WBCIR_IRQ_ERR);
}