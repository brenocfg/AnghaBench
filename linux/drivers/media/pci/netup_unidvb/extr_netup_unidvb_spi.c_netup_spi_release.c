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
typedef  int u16 ;
struct netup_unidvb_dev {struct netup_spi* spi; } ;
struct netup_spi {int /*<<< orphan*/  master; int /*<<< orphan*/  lock; TYPE_1__* regs; } ;
struct TYPE_2__ {int /*<<< orphan*/  control_stat; } ;

/* Variables and functions */
 int NETUP_SPI_CTRL_IMASK ; 
 int NETUP_SPI_CTRL_IRQ ; 
 int readw (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spi_unregister_master (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writew (int,int /*<<< orphan*/ *) ; 

void netup_spi_release(struct netup_unidvb_dev *ndev)
{
	u16 reg;
	unsigned long flags;
	struct netup_spi *spi = ndev->spi;

	if (!spi)
		return;

	spin_lock_irqsave(&spi->lock, flags);
	reg = readw(&spi->regs->control_stat);
	writew(reg | NETUP_SPI_CTRL_IRQ, &spi->regs->control_stat);
	reg = readw(&spi->regs->control_stat);
	writew(reg & ~NETUP_SPI_CTRL_IMASK, &spi->regs->control_stat);
	spin_unlock_irqrestore(&spi->lock, flags);
	spi_unregister_master(spi->master);
	ndev->spi = NULL;
}