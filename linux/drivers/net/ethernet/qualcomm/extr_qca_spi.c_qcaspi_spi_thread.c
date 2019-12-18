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
typedef  int u16 ;
struct TYPE_4__ {int /*<<< orphan*/  write_buf_err; int /*<<< orphan*/  read_buf_err; int /*<<< orphan*/  device_reset; } ;
struct TYPE_3__ {size_t head; int /*<<< orphan*/ ** skb; } ;
struct qcaspi {scalar_t__ intr_req; scalar_t__ intr_svc; scalar_t__ sync; int /*<<< orphan*/  net_dev; TYPE_2__ stats; TYPE_1__ txr; } ;

/* Variables and functions */
 int /*<<< orphan*/  QCASPI_EVENT_CPUON ; 
 int /*<<< orphan*/  QCASPI_EVENT_UPDATE ; 
 int /*<<< orphan*/  QCASPI_QCA7K_REBOOT_TIME_MS ; 
 scalar_t__ QCASPI_SYNC_READY ; 
 void* QCASPI_SYNC_UNKNOWN ; 
 int SPI_INT_CPU_ON ; 
 int SPI_INT_PKT_AVLBL ; 
 int SPI_INT_RDBUF_ERR ; 
 int SPI_INT_WRBUF_ERR ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  TASK_RUNNING ; 
 int /*<<< orphan*/  end_spi_intr_handling (struct qcaspi*,int) ; 
 int /*<<< orphan*/  kthread_should_stop () ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  netdev_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  netif_carrier_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_carrier_on (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_stop_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_wake_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qcaspi_flush_tx_ring (struct qcaspi*) ; 
 int /*<<< orphan*/  qcaspi_qca7k_sync (struct qcaspi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qcaspi_receive (struct qcaspi*) ; 
 int /*<<< orphan*/  qcaspi_transmit (struct qcaspi*) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  start_spi_intr_handling (struct qcaspi*,int*) ; 

__attribute__((used)) static int
qcaspi_spi_thread(void *data)
{
	struct qcaspi *qca = data;
	u16 intr_cause = 0;

	netdev_info(qca->net_dev, "SPI thread created\n");
	while (!kthread_should_stop()) {
		set_current_state(TASK_INTERRUPTIBLE);
		if ((qca->intr_req == qca->intr_svc) &&
		    (qca->txr.skb[qca->txr.head] == NULL) &&
		    (qca->sync == QCASPI_SYNC_READY))
			schedule();

		set_current_state(TASK_RUNNING);

		netdev_dbg(qca->net_dev, "have work to do. int: %d, tx_skb: %p\n",
			   qca->intr_req - qca->intr_svc,
			   qca->txr.skb[qca->txr.head]);

		qcaspi_qca7k_sync(qca, QCASPI_EVENT_UPDATE);

		if (qca->sync != QCASPI_SYNC_READY) {
			netdev_dbg(qca->net_dev, "sync: not ready %u, turn off carrier and flush\n",
				   (unsigned int)qca->sync);
			netif_stop_queue(qca->net_dev);
			netif_carrier_off(qca->net_dev);
			qcaspi_flush_tx_ring(qca);
			msleep(QCASPI_QCA7K_REBOOT_TIME_MS);
		}

		if (qca->intr_svc != qca->intr_req) {
			qca->intr_svc = qca->intr_req;
			start_spi_intr_handling(qca, &intr_cause);

			if (intr_cause & SPI_INT_CPU_ON) {
				qcaspi_qca7k_sync(qca, QCASPI_EVENT_CPUON);

				/* not synced. */
				if (qca->sync != QCASPI_SYNC_READY)
					continue;

				qca->stats.device_reset++;
				netif_wake_queue(qca->net_dev);
				netif_carrier_on(qca->net_dev);
			}

			if (intr_cause & SPI_INT_RDBUF_ERR) {
				/* restart sync */
				netdev_dbg(qca->net_dev, "===> rdbuf error!\n");
				qca->stats.read_buf_err++;
				qca->sync = QCASPI_SYNC_UNKNOWN;
				continue;
			}

			if (intr_cause & SPI_INT_WRBUF_ERR) {
				/* restart sync */
				netdev_dbg(qca->net_dev, "===> wrbuf error!\n");
				qca->stats.write_buf_err++;
				qca->sync = QCASPI_SYNC_UNKNOWN;
				continue;
			}

			/* can only handle other interrupts
			 * if sync has occurred
			 */
			if (qca->sync == QCASPI_SYNC_READY) {
				if (intr_cause & SPI_INT_PKT_AVLBL)
					qcaspi_receive(qca);
			}

			end_spi_intr_handling(qca, intr_cause);
		}

		if (qca->sync == QCASPI_SYNC_READY)
			qcaspi_transmit(qca);
	}
	set_current_state(TASK_RUNNING);
	netdev_info(qca->net_dev, "SPI thread exit\n");

	return 0;
}