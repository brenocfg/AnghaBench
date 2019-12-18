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
struct spi_transfer {int len; int /*<<< orphan*/ * rx_buf; int /*<<< orphan*/ * tx_buf; } ;
struct spi_message {int dummy; } ;
struct ks8851_net {int /*<<< orphan*/  netdev; int /*<<< orphan*/  spidev; struct spi_message spi_msg1; struct spi_transfer spi_xfer1; } ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 unsigned int KS_SPIOP_WR ; 
 unsigned int MK_OP (int,unsigned int) ; 
 int /*<<< orphan*/  cpu_to_le16 (unsigned int) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 
 int spi_sync (int /*<<< orphan*/ ,struct spi_message*) ; 

__attribute__((used)) static void ks8851_wrreg16(struct ks8851_net *ks, unsigned reg, unsigned val)
{
	struct spi_transfer *xfer = &ks->spi_xfer1;
	struct spi_message *msg = &ks->spi_msg1;
	__le16 txb[2];
	int ret;

	txb[0] = cpu_to_le16(MK_OP(reg & 2 ? 0xC : 0x03, reg) | KS_SPIOP_WR);
	txb[1] = cpu_to_le16(val);

	xfer->tx_buf = txb;
	xfer->rx_buf = NULL;
	xfer->len = 4;

	ret = spi_sync(ks->spidev, msg);
	if (ret < 0)
		netdev_err(ks->netdev, "spi_sync() failed\n");
}