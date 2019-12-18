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
struct qcaspi {int /*<<< orphan*/ * spi_thread; TYPE_1__* spi_dev; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPI_REG_INTR_ENABLE ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct qcaspi*) ; 
 int /*<<< orphan*/  kthread_stop (int /*<<< orphan*/ *) ; 
 struct qcaspi* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  qcaspi_flush_tx_ring (struct qcaspi*) ; 
 int /*<<< orphan*/  qcaspi_write_register (struct qcaspi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wr_verify ; 

__attribute__((used)) static int
qcaspi_netdev_close(struct net_device *dev)
{
	struct qcaspi *qca = netdev_priv(dev);

	netif_stop_queue(dev);

	qcaspi_write_register(qca, SPI_REG_INTR_ENABLE, 0, wr_verify);
	free_irq(qca->spi_dev->irq, qca);

	kthread_stop(qca->spi_thread);
	qca->spi_thread = NULL;
	qcaspi_flush_tx_ring(qca);

	return 0;
}