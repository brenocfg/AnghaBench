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

/* Variables and functions */
 int AU1100_GPIO14_INT ; 
 int AU1100_GPIO19_INT ; 
 int /*<<< orphan*/  BCSR_WHOAMI ; 
 scalar_t__ BCSR_WHOAMI_BOARD (int /*<<< orphan*/ ) ; 
 scalar_t__ BCSR_WHOAMI_DB1100 ; 
 int /*<<< orphan*/  IRQ_TYPE_EDGE_BOTH ; 
 int /*<<< orphan*/  bcsr_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  db1100_mmc_cd ; 
 int /*<<< orphan*/  free_irq (int,void*) ; 
 int /*<<< orphan*/  irq_set_irq_type (int,int /*<<< orphan*/ ) ; 
 int request_irq (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,void*) ; 

__attribute__((used)) static int db1100_mmc_cd_setup(void *mmc_host, int en)
{
	int ret = 0, irq;

	if (BCSR_WHOAMI_BOARD(bcsr_read(BCSR_WHOAMI)) == BCSR_WHOAMI_DB1100)
		irq = AU1100_GPIO19_INT;
	else
		irq = AU1100_GPIO14_INT;	/* PB1100 SD0 CD# */

	if (en) {
		irq_set_irq_type(irq, IRQ_TYPE_EDGE_BOTH);
		ret = request_irq(irq, db1100_mmc_cd, 0,
				  "sd0_cd", mmc_host);
	} else
		free_irq(irq, mmc_host);
	return ret;
}