#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct qcaspi {scalar_t__ spi_thread; int /*<<< orphan*/  sync; TYPE_2__* net_dev; } ;
struct net_device {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  tx_errors; } ;
struct TYPE_4__ {TYPE_1__ stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  QCASPI_SYNC_UNKNOWN ; 
 scalar_t__ dev_trans_start (struct net_device*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  netdev_info (TYPE_2__*,char*,scalar_t__,scalar_t__) ; 
 struct qcaspi* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  wake_up_process (scalar_t__) ; 

__attribute__((used)) static void
qcaspi_netdev_tx_timeout(struct net_device *dev)
{
	struct qcaspi *qca = netdev_priv(dev);

	netdev_info(qca->net_dev, "Transmit timeout at %ld, latency %ld\n",
		    jiffies, jiffies - dev_trans_start(dev));
	qca->net_dev->stats.tx_errors++;
	/* Trigger tx queue flush and QCA7000 reset */
	qca->sync = QCASPI_SYNC_UNKNOWN;

	if (qca->spi_thread)
		wake_up_process(qca->spi_thread);
}