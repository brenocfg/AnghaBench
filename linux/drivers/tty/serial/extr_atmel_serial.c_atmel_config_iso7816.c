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
struct serial_iso7816 {int flags; int tg; } ;
struct uart_port {struct serial_iso7816 iso7816; int /*<<< orphan*/  dev; } ;
struct atmel_uart_port {unsigned int tx_done_mask; unsigned int fidi_min; unsigned int fidi_max; unsigned int backup_mode; unsigned int backup_brgr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATMEL_US_BRGR ; 
 unsigned int ATMEL_US_CLKO ; 
 int /*<<< orphan*/  ATMEL_US_CR ; 
 unsigned int ATMEL_US_DSNACK ; 
 int ATMEL_US_ENDTX ; 
 int /*<<< orphan*/  ATMEL_US_FIDI ; 
 int /*<<< orphan*/  ATMEL_US_IDR ; 
 int /*<<< orphan*/  ATMEL_US_IER ; 
 unsigned int ATMEL_US_INACK ; 
 int ATMEL_US_ITERATION ; 
 unsigned int ATMEL_US_MAX_ITER (int) ; 
 int /*<<< orphan*/  ATMEL_US_MR ; 
 int ATMEL_US_NACK ; 
 unsigned int ATMEL_US_NBSTOP ; 
 unsigned int ATMEL_US_NBSTOP_1 ; 
 unsigned int ATMEL_US_PAR ; 
 unsigned int ATMEL_US_PAR_EVEN ; 
 unsigned int ATMEL_US_RXEN ; 
 int /*<<< orphan*/  ATMEL_US_TTGR ; 
 int ATMEL_US_TXBUFE ; 
 unsigned int ATMEL_US_TXDIS ; 
 int ATMEL_US_TXEMPTY ; 
 int ATMEL_US_TXRDY ; 
 unsigned int ATMEL_US_USCLKS ; 
 unsigned int ATMEL_US_USCLKS_MCK ; 
 unsigned int ATMEL_US_USMODE ; 
 unsigned int ATMEL_US_USMODE_ISO7816_T0 ; 
 unsigned int ATMEL_US_USMODE_ISO7816_T1 ; 
 int EINVAL ; 
 int SER_ISO7816_ENABLED ; 
 int SER_ISO7816_T (int) ; 
 int SER_ISO7816_T_PARAM ; 
 unsigned int atmel_calc_cd (struct uart_port*,struct serial_iso7816*) ; 
 unsigned int atmel_calc_fidi (struct uart_port*,struct serial_iso7816*) ; 
 void* atmel_uart_readl (struct uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atmel_uart_writel (struct uart_port*,int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ atmel_use_pdc_tx (struct uart_port*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memset (struct serial_iso7816*,int /*<<< orphan*/ ,int) ; 
 struct atmel_uart_port* to_atmel_uart_port (struct uart_port*) ; 

__attribute__((used)) static int atmel_config_iso7816(struct uart_port *port,
				struct serial_iso7816 *iso7816conf)
{
	struct atmel_uart_port *atmel_port = to_atmel_uart_port(port);
	unsigned int mode;
	unsigned int cd, fidi;
	int ret = 0;

	/* Disable interrupts */
	atmel_uart_writel(port, ATMEL_US_IDR, atmel_port->tx_done_mask);

	mode = atmel_uart_readl(port, ATMEL_US_MR);

	if (iso7816conf->flags & SER_ISO7816_ENABLED) {
		mode &= ~ATMEL_US_USMODE;

		if (iso7816conf->tg > 255) {
			dev_err(port->dev, "ISO7816: Timeguard exceeding 255\n");
			memset(iso7816conf, 0, sizeof(struct serial_iso7816));
			ret = -EINVAL;
			goto err_out;
		}

		if ((iso7816conf->flags & SER_ISO7816_T_PARAM)
		    == SER_ISO7816_T(0)) {
			mode |= ATMEL_US_USMODE_ISO7816_T0 | ATMEL_US_DSNACK;
		} else if ((iso7816conf->flags & SER_ISO7816_T_PARAM)
			   == SER_ISO7816_T(1)) {
			mode |= ATMEL_US_USMODE_ISO7816_T1 | ATMEL_US_INACK;
		} else {
			dev_err(port->dev, "ISO7816: Type not supported\n");
			memset(iso7816conf, 0, sizeof(struct serial_iso7816));
			ret = -EINVAL;
			goto err_out;
		}

		mode &= ~(ATMEL_US_USCLKS | ATMEL_US_NBSTOP | ATMEL_US_PAR);

		/* select mck clock, and output  */
		mode |= ATMEL_US_USCLKS_MCK | ATMEL_US_CLKO;
		/* set parity for normal/inverse mode + max iterations */
		mode |= ATMEL_US_PAR_EVEN | ATMEL_US_NBSTOP_1 | ATMEL_US_MAX_ITER(3);

		cd = atmel_calc_cd(port, iso7816conf);
		fidi = atmel_calc_fidi(port, iso7816conf);
		if (fidi == 0) {
			dev_warn(port->dev, "ISO7816 fidi = 0, Generator generates no signal\n");
		} else if (fidi < atmel_port->fidi_min
			   || fidi > atmel_port->fidi_max) {
			dev_err(port->dev, "ISO7816 fidi = %u, value not supported\n", fidi);
			memset(iso7816conf, 0, sizeof(struct serial_iso7816));
			ret = -EINVAL;
			goto err_out;
		}

		if (!(port->iso7816.flags & SER_ISO7816_ENABLED)) {
			/* port not yet in iso7816 mode: store configuration */
			atmel_port->backup_mode = atmel_uart_readl(port, ATMEL_US_MR);
			atmel_port->backup_brgr = atmel_uart_readl(port, ATMEL_US_BRGR);
		}

		atmel_uart_writel(port, ATMEL_US_TTGR, iso7816conf->tg);
		atmel_uart_writel(port, ATMEL_US_BRGR, cd);
		atmel_uart_writel(port, ATMEL_US_FIDI, fidi);

		atmel_uart_writel(port, ATMEL_US_CR, ATMEL_US_TXDIS | ATMEL_US_RXEN);
		atmel_port->tx_done_mask = ATMEL_US_TXEMPTY | ATMEL_US_NACK | ATMEL_US_ITERATION;
	} else {
		dev_dbg(port->dev, "Setting UART back to RS232\n");
		/* back to last RS232 settings */
		mode = atmel_port->backup_mode;
		memset(iso7816conf, 0, sizeof(struct serial_iso7816));
		atmel_uart_writel(port, ATMEL_US_TTGR, 0);
		atmel_uart_writel(port, ATMEL_US_BRGR, atmel_port->backup_brgr);
		atmel_uart_writel(port, ATMEL_US_FIDI, 0x174);

		if (atmel_use_pdc_tx(port))
			atmel_port->tx_done_mask = ATMEL_US_ENDTX |
						   ATMEL_US_TXBUFE;
		else
			atmel_port->tx_done_mask = ATMEL_US_TXRDY;
	}

	port->iso7816 = *iso7816conf;

	atmel_uart_writel(port, ATMEL_US_MR, mode);

err_out:
	/* Enable interrupts */
	atmel_uart_writel(port, ATMEL_US_IER, atmel_port->tx_done_mask);

	return ret;
}