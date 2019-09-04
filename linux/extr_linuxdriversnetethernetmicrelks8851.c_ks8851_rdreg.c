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
typedef  int /*<<< orphan*/  u8 ;
struct spi_transfer {int len; int /*<<< orphan*/ * rx_buf; int /*<<< orphan*/ * tx_buf; } ;
struct spi_message {int dummy; } ;
struct ks8851_net {TYPE_2__* spidev; int /*<<< orphan*/  netdev; struct spi_transfer spi_xfer1; struct spi_message spi_msg1; struct spi_transfer* spi_xfer2; struct spi_message spi_msg2; int /*<<< orphan*/ * rxd; scalar_t__ txd; } ;
typedef  int /*<<< orphan*/  __le16 ;
struct TYPE_4__ {TYPE_1__* master; } ;
struct TYPE_3__ {int flags; } ;

/* Variables and functions */
 unsigned int KS_SPIOP_RD ; 
 int SPI_MASTER_HALF_DUPLEX ; 
 int /*<<< orphan*/  cpu_to_le16 (unsigned int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 
 int spi_sync (TYPE_2__*,struct spi_message*) ; 

__attribute__((used)) static void ks8851_rdreg(struct ks8851_net *ks, unsigned op,
			 u8 *rxb, unsigned rxl)
{
	struct spi_transfer *xfer;
	struct spi_message *msg;
	__le16 *txb = (__le16 *)ks->txd;
	u8 *trx = ks->rxd;
	int ret;

	txb[0] = cpu_to_le16(op | KS_SPIOP_RD);

	if (ks->spidev->master->flags & SPI_MASTER_HALF_DUPLEX) {
		msg = &ks->spi_msg2;
		xfer = ks->spi_xfer2;

		xfer->tx_buf = txb;
		xfer->rx_buf = NULL;
		xfer->len = 2;

		xfer++;
		xfer->tx_buf = NULL;
		xfer->rx_buf = trx;
		xfer->len = rxl;
	} else {
		msg = &ks->spi_msg1;
		xfer = &ks->spi_xfer1;

		xfer->tx_buf = txb;
		xfer->rx_buf = trx;
		xfer->len = rxl + 2;
	}

	ret = spi_sync(ks->spidev, msg);
	if (ret < 0)
		netdev_err(ks->netdev, "read: spi_sync() failed\n");
	else if (ks->spidev->master->flags & SPI_MASTER_HALF_DUPLEX)
		memcpy(rxb, trx, rxl);
	else
		memcpy(rxb, trx + 2, rxl);
}