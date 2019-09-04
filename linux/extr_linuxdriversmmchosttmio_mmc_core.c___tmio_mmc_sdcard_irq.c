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
struct tmio_mmc_host {int dummy; } ;

/* Variables and functions */
 int TMIO_STAT_CMDRESPEND ; 
 int TMIO_STAT_CMDTIMEOUT ; 
 int TMIO_STAT_DATAEND ; 
 int TMIO_STAT_RXRDY ; 
 int TMIO_STAT_TXRQ ; 
 int /*<<< orphan*/  tmio_mmc_ack_mmc_irqs (struct tmio_mmc_host*,int) ; 
 int /*<<< orphan*/  tmio_mmc_cmd_irq (struct tmio_mmc_host*,int) ; 
 int /*<<< orphan*/  tmio_mmc_data_irq (struct tmio_mmc_host*,int) ; 
 int /*<<< orphan*/  tmio_mmc_pio_irq (struct tmio_mmc_host*) ; 

__attribute__((used)) static bool __tmio_mmc_sdcard_irq(struct tmio_mmc_host *host, int ireg,
				  int status)
{
	/* Command completion */
	if (ireg & (TMIO_STAT_CMDRESPEND | TMIO_STAT_CMDTIMEOUT)) {
		tmio_mmc_ack_mmc_irqs(host, TMIO_STAT_CMDRESPEND |
				      TMIO_STAT_CMDTIMEOUT);
		tmio_mmc_cmd_irq(host, status);
		return true;
	}

	/* Data transfer */
	if (ireg & (TMIO_STAT_RXRDY | TMIO_STAT_TXRQ)) {
		tmio_mmc_ack_mmc_irqs(host, TMIO_STAT_RXRDY | TMIO_STAT_TXRQ);
		tmio_mmc_pio_irq(host);
		return true;
	}

	/* Data transfer completion */
	if (ireg & TMIO_STAT_DATAEND) {
		tmio_mmc_ack_mmc_irqs(host, TMIO_STAT_DATAEND);
		tmio_mmc_data_irq(host, status);
		return true;
	}

	return false;
}