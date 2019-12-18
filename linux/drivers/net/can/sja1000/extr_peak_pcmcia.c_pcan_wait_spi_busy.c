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
struct pcan_pccard {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  PCC_CSR ; 
 int PCC_CSR_SPI_BUSY ; 
 int /*<<< orphan*/  PCC_SPI_MAX_BUSY_WAIT_MS ; 
 int jiffies ; 
 int msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int pcan_read_reg (struct pcan_pccard*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule () ; 
 scalar_t__ time_after (int,unsigned long) ; 

__attribute__((used)) static int pcan_wait_spi_busy(struct pcan_pccard *card)
{
	unsigned long timeout = jiffies +
				msecs_to_jiffies(PCC_SPI_MAX_BUSY_WAIT_MS) + 1;

	/* be sure to read status at least once after sleeping */
	while (pcan_read_reg(card, PCC_CSR) & PCC_CSR_SPI_BUSY) {
		if (time_after(jiffies, timeout))
			return -EBUSY;
		schedule();
	}

	return 0;
}