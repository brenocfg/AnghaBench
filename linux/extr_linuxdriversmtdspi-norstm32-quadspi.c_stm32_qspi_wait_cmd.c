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
typedef  int u32 ;
struct stm32_qspi {scalar_t__ io_base; int /*<<< orphan*/  cmd_completion; } ;

/* Variables and functions */
 int CR_TCIE ; 
 int ETIMEDOUT ; 
 scalar_t__ QUADSPI_CR ; 
 scalar_t__ QUADSPI_SR ; 
 int SR_TCF ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_for_completion_interruptible_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static int stm32_qspi_wait_cmd(struct stm32_qspi *qspi)
{
	u32 cr;
	int err = 0;

	if (readl_relaxed(qspi->io_base + QUADSPI_SR) & SR_TCF)
		return 0;

	reinit_completion(&qspi->cmd_completion);
	cr = readl_relaxed(qspi->io_base + QUADSPI_CR);
	writel_relaxed(cr | CR_TCIE, qspi->io_base + QUADSPI_CR);

	if (!wait_for_completion_interruptible_timeout(&qspi->cmd_completion,
						       msecs_to_jiffies(1000)))
		err = -ETIMEDOUT;

	writel_relaxed(cr, qspi->io_base + QUADSPI_CR);
	return err;
}