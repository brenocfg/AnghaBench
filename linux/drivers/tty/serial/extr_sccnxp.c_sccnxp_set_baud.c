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
typedef  size_t u8 ;
struct uart_port {int /*<<< orphan*/  dev; int /*<<< orphan*/  uartclk; } ;
struct sccnxp_port {struct sccnxp_chip* chip; } ;
struct sccnxp_chip {int flags; int /*<<< orphan*/  freq_std; } ;
struct TYPE_2__ {int baud; size_t mr0; size_t acr; size_t csr; } ;

/* Variables and functions */
 size_t ACR_TIMER_MODE ; 
 size_t CR_CMD_MRPTR0 ; 
 size_t CSR_TIMER_MODE ; 
 int DIV_ROUND_CLOSEST (int /*<<< orphan*/ ,int) ; 
 int INT_MAX ; 
 size_t MR0_FIFO ; 
 size_t MR0_TXLVL ; 
 int /*<<< orphan*/  SCCNXP_ACR_REG ; 
 int /*<<< orphan*/  SCCNXP_CR_REG ; 
 int /*<<< orphan*/  SCCNXP_CSR_REG ; 
 int /*<<< orphan*/  SCCNXP_CTPL_REG ; 
 int /*<<< orphan*/  SCCNXP_CTPU_REG ; 
 int SCCNXP_HAVE_MR0 ; 
 int /*<<< orphan*/  SCCNXP_MR_REG ; 
 int /*<<< orphan*/  SCCNXP_START_COUNTER_REG ; 
 TYPE_1__* baud_std ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int) ; 
 struct sccnxp_port* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sccnxp_port_read (struct uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sccnxp_port_write (struct uart_port*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  sccnxp_update_best_err (int,int,int*) ; 

__attribute__((used)) static int sccnxp_set_baud(struct uart_port *port, int baud)
{
	struct sccnxp_port *s = dev_get_drvdata(port->dev);
	int div_std, tmp_baud, bestbaud = INT_MAX, besterr = INT_MAX;
	struct sccnxp_chip *chip = s->chip;
	u8 i, acr = 0, csr = 0, mr0 = 0;

	/* Find divisor to load to the timer preset registers */
	div_std = DIV_ROUND_CLOSEST(port->uartclk, 2 * 16 * baud);
	if ((div_std >= 2) && (div_std <= 0xffff)) {
		bestbaud = DIV_ROUND_CLOSEST(port->uartclk, 2 * 16 * div_std);
		sccnxp_update_best_err(baud, bestbaud, &besterr);
		csr = CSR_TIMER_MODE;
		sccnxp_port_write(port, SCCNXP_CTPU_REG, div_std >> 8);
		sccnxp_port_write(port, SCCNXP_CTPL_REG, div_std);
		/* Issue start timer/counter command */
		sccnxp_port_read(port, SCCNXP_START_COUNTER_REG);
	}

	/* Find best baud from table */
	for (i = 0; baud_std[i].baud && besterr; i++) {
		if (baud_std[i].mr0 && !(chip->flags & SCCNXP_HAVE_MR0))
			continue;
		div_std = DIV_ROUND_CLOSEST(chip->freq_std, baud_std[i].baud);
		tmp_baud = DIV_ROUND_CLOSEST(port->uartclk, div_std);
		if (!sccnxp_update_best_err(baud, tmp_baud, &besterr)) {
			acr = baud_std[i].acr;
			csr = baud_std[i].csr;
			mr0 = baud_std[i].mr0;
			bestbaud = tmp_baud;
		}
	}

	if (chip->flags & SCCNXP_HAVE_MR0) {
		/* Enable FIFO, set half level for TX */
		mr0 |= MR0_FIFO | MR0_TXLVL;
		/* Update MR0 */
		sccnxp_port_write(port, SCCNXP_CR_REG, CR_CMD_MRPTR0);
		sccnxp_port_write(port, SCCNXP_MR_REG, mr0);
	}

	sccnxp_port_write(port, SCCNXP_ACR_REG, acr | ACR_TIMER_MODE);
	sccnxp_port_write(port, SCCNXP_CSR_REG, (csr << 4) | csr);

	if (baud != bestbaud)
		dev_dbg(port->dev, "Baudrate desired: %i, calculated: %i\n",
			baud, bestbaud);

	return bestbaud;
}