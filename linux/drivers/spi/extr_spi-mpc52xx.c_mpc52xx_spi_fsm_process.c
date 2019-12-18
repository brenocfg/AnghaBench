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
typedef  int /*<<< orphan*/  u8 ;
struct mpc52xx_spi {int (* state ) (int,struct mpc52xx_spi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  work; scalar_t__ regs; } ;

/* Variables and functions */
 int FSM_CONTINUE ; 
 int FSM_POLL ; 
 scalar_t__ SPI_DATA ; 
 scalar_t__ SPI_STATUS ; 
 int /*<<< orphan*/  in_8 (scalar_t__) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int stub1 (int,struct mpc52xx_spi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mpc52xx_spi_fsm_process(int irq, struct mpc52xx_spi *ms)
{
	int rc = FSM_CONTINUE;
	u8 status, data;

	while (rc == FSM_CONTINUE) {
		/* Interrupt cleared by read of STATUS followed by
		 * read of DATA registers */
		status = in_8(ms->regs + SPI_STATUS);
		data = in_8(ms->regs + SPI_DATA);
		rc = ms->state(irq, ms, status, data);
	}

	if (rc == FSM_POLL)
		schedule_work(&ms->work);
}