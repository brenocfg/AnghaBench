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
typedef  scalar_t__ u16 ;
struct TYPE_2__ {int /*<<< orphan*/  reset_timeout; int /*<<< orphan*/  trig_reset; } ;
struct qcaspi {int sync; int /*<<< orphan*/  net_dev; TYPE_1__ stats; } ;

/* Variables and functions */
 int QCASPI_EVENT_CPUON ; 
 scalar_t__ QCASPI_GOOD_SIGNATURE ; 
 scalar_t__ QCASPI_HW_BUF_LEN ; 
 scalar_t__ QCASPI_RESET_TIMEOUT ; 
 scalar_t__ QCASPI_SLAVE_RESET_BIT ; 
#define  QCASPI_SYNC_READY 130 
#define  QCASPI_SYNC_RESET 129 
#define  QCASPI_SYNC_UNKNOWN 128 
 int /*<<< orphan*/  SPI_REG_SIGNATURE ; 
 int /*<<< orphan*/  SPI_REG_SPI_CONFIG ; 
 int /*<<< orphan*/  SPI_REG_WRBUF_SPC_AVA ; 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  qcaspi_read_register (struct qcaspi*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  qcaspi_write_register (struct qcaspi*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
qcaspi_qca7k_sync(struct qcaspi *qca, int event)
{
	u16 signature = 0;
	u16 spi_config;
	u16 wrbuf_space = 0;
	static u16 reset_count;

	if (event == QCASPI_EVENT_CPUON) {
		/* Read signature twice, if not valid
		 * go back to unknown state.
		 */
		qcaspi_read_register(qca, SPI_REG_SIGNATURE, &signature);
		qcaspi_read_register(qca, SPI_REG_SIGNATURE, &signature);
		if (signature != QCASPI_GOOD_SIGNATURE) {
			qca->sync = QCASPI_SYNC_UNKNOWN;
			netdev_dbg(qca->net_dev, "sync: got CPU on, but signature was invalid, restart\n");
		} else {
			/* ensure that the WRBUF is empty */
			qcaspi_read_register(qca, SPI_REG_WRBUF_SPC_AVA,
					     &wrbuf_space);
			if (wrbuf_space != QCASPI_HW_BUF_LEN) {
				netdev_dbg(qca->net_dev, "sync: got CPU on, but wrbuf not empty. reset!\n");
				qca->sync = QCASPI_SYNC_UNKNOWN;
			} else {
				netdev_dbg(qca->net_dev, "sync: got CPU on, now in sync\n");
				qca->sync = QCASPI_SYNC_READY;
				return;
			}
		}
	}

	switch (qca->sync) {
	case QCASPI_SYNC_READY:
		/* Read signature, if not valid go to unknown state. */
		qcaspi_read_register(qca, SPI_REG_SIGNATURE, &signature);
		if (signature != QCASPI_GOOD_SIGNATURE) {
			qca->sync = QCASPI_SYNC_UNKNOWN;
			netdev_dbg(qca->net_dev, "sync: bad signature, restart\n");
			/* don't reset right away */
			return;
		}
		break;
	case QCASPI_SYNC_UNKNOWN:
		/* Read signature, if not valid stay in unknown state */
		qcaspi_read_register(qca, SPI_REG_SIGNATURE, &signature);
		if (signature != QCASPI_GOOD_SIGNATURE) {
			netdev_dbg(qca->net_dev, "sync: could not read signature to reset device, retry.\n");
			return;
		}

		/* TODO: use GPIO to reset QCA7000 in legacy mode*/
		netdev_dbg(qca->net_dev, "sync: resetting device.\n");
		qcaspi_read_register(qca, SPI_REG_SPI_CONFIG, &spi_config);
		spi_config |= QCASPI_SLAVE_RESET_BIT;
		qcaspi_write_register(qca, SPI_REG_SPI_CONFIG, spi_config, 0);

		qca->sync = QCASPI_SYNC_RESET;
		qca->stats.trig_reset++;
		reset_count = 0;
		break;
	case QCASPI_SYNC_RESET:
		reset_count++;
		netdev_dbg(qca->net_dev, "sync: waiting for CPU on, count %u.\n",
			   reset_count);
		if (reset_count >= QCASPI_RESET_TIMEOUT) {
			/* reset did not seem to take place, try again */
			qca->sync = QCASPI_SYNC_UNKNOWN;
			qca->stats.reset_timeout++;
			netdev_dbg(qca->net_dev, "sync: reset timeout, restarting process.\n");
		}
		break;
	}
}