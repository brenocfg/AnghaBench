#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
typedef  scalar_t__ u16 ;
struct TYPE_6__ {int /*<<< orphan*/  out_of_mem; int /*<<< orphan*/  read_err; int /*<<< orphan*/  buf_avail_err; } ;
struct qcaspi {scalar_t__ burst_len; TYPE_1__ stats; TYPE_2__* rx_skb; struct net_device* net_dev; int /*<<< orphan*/  frm_handle; int /*<<< orphan*/ * rx_buffer; scalar_t__ legacy_mode; } ;
struct net_device_stats {int rx_bytes; int /*<<< orphan*/  rx_errors; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  rx_dropped; } ;
struct net_device {scalar_t__ mtu; struct net_device_stats stats; } ;
typedef  int s32 ;
struct TYPE_7__ {int /*<<< orphan*/  ip_summed; struct net_device* dev; int /*<<< orphan*/  protocol; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECKSUM_UNNECESSARY ; 
 int QCA7K_SPI_EXTERNAL ; 
 int QCA7K_SPI_READ ; 
#define  QCAFRM_GATHER 131 
#define  QCAFRM_INVLEN 130 
#define  QCAFRM_NOHEAD 129 
#define  QCAFRM_NOTAIL 128 
 scalar_t__ QCASPI_HW_BUF_LEN ; 
 int /*<<< orphan*/  SPI_REG_BFR_SIZE ; 
 int /*<<< orphan*/  SPI_REG_RDBUF_BYTE_AVA ; 
 scalar_t__ VLAN_ETH_HLEN ; 
 int /*<<< orphan*/  eth_type_trans (TYPE_2__*,struct net_device*) ; 
 void* netdev_alloc_skb_ip_align (struct net_device*,scalar_t__) ; 
 int /*<<< orphan*/  netdev_dbg (struct net_device*,char*,...) ; 
 int /*<<< orphan*/  netif_rx_ni (TYPE_2__*) ; 
 int qcafrm_fsm_decode (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ qcaspi_read_burst (struct qcaspi*,int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ qcaspi_read_legacy (struct qcaspi*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  qcaspi_read_register (struct qcaspi*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  qcaspi_tx_cmd (struct qcaspi*,int) ; 
 int /*<<< orphan*/  qcaspi_write_register (struct qcaspi*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_put (TYPE_2__*,int) ; 
 int /*<<< orphan*/  skb_tailroom (TYPE_2__*) ; 
 int /*<<< orphan*/  wr_verify ; 

__attribute__((used)) static int
qcaspi_receive(struct qcaspi *qca)
{
	struct net_device *net_dev = qca->net_dev;
	struct net_device_stats *n_stats = &net_dev->stats;
	u16 available = 0;
	u32 bytes_read;
	u8 *cp;

	/* Allocate rx SKB if we don't have one available. */
	if (!qca->rx_skb) {
		qca->rx_skb = netdev_alloc_skb_ip_align(net_dev,
							net_dev->mtu +
							VLAN_ETH_HLEN);
		if (!qca->rx_skb) {
			netdev_dbg(net_dev, "out of RX resources\n");
			qca->stats.out_of_mem++;
			return -1;
		}
	}

	/* Read the packet size. */
	qcaspi_read_register(qca, SPI_REG_RDBUF_BYTE_AVA, &available);

	netdev_dbg(net_dev, "qcaspi_receive: SPI_REG_RDBUF_BYTE_AVA: Value: %08x\n",
		   available);

	if (available > QCASPI_HW_BUF_LEN) {
		/* This could only happen by interferences on the SPI line.
		 * So retry later ...
		 */
		qca->stats.buf_avail_err++;
		return -1;
	} else if (available == 0) {
		netdev_dbg(net_dev, "qcaspi_receive called without any data being available!\n");
		return -1;
	}

	qcaspi_write_register(qca, SPI_REG_BFR_SIZE, available, wr_verify);

	if (qca->legacy_mode)
		qcaspi_tx_cmd(qca, QCA7K_SPI_READ | QCA7K_SPI_EXTERNAL);

	while (available) {
		u32 count = available;

		if (count > qca->burst_len)
			count = qca->burst_len;

		if (qca->legacy_mode) {
			bytes_read = qcaspi_read_legacy(qca, qca->rx_buffer,
							count);
		} else {
			bytes_read = qcaspi_read_burst(qca, qca->rx_buffer,
						       count);
		}

		netdev_dbg(net_dev, "available: %d, byte read: %d\n",
			   available, bytes_read);

		if (bytes_read) {
			available -= bytes_read;
		} else {
			qca->stats.read_err++;
			return -1;
		}

		cp = qca->rx_buffer;

		while ((bytes_read--) && (qca->rx_skb)) {
			s32 retcode;

			retcode = qcafrm_fsm_decode(&qca->frm_handle,
						    qca->rx_skb->data,
						    skb_tailroom(qca->rx_skb),
						    *cp);
			cp++;
			switch (retcode) {
			case QCAFRM_GATHER:
			case QCAFRM_NOHEAD:
				break;
			case QCAFRM_NOTAIL:
				netdev_dbg(net_dev, "no RX tail\n");
				n_stats->rx_errors++;
				n_stats->rx_dropped++;
				break;
			case QCAFRM_INVLEN:
				netdev_dbg(net_dev, "invalid RX length\n");
				n_stats->rx_errors++;
				n_stats->rx_dropped++;
				break;
			default:
				qca->rx_skb->dev = qca->net_dev;
				n_stats->rx_packets++;
				n_stats->rx_bytes += retcode;
				skb_put(qca->rx_skb, retcode);
				qca->rx_skb->protocol = eth_type_trans(
					qca->rx_skb, qca->rx_skb->dev);
				qca->rx_skb->ip_summed = CHECKSUM_UNNECESSARY;
				netif_rx_ni(qca->rx_skb);
				qca->rx_skb = netdev_alloc_skb_ip_align(net_dev,
					net_dev->mtu + VLAN_ETH_HLEN);
				if (!qca->rx_skb) {
					netdev_dbg(net_dev, "out of RX resources\n");
					n_stats->rx_errors++;
					qca->stats.out_of_mem++;
					break;
				}
			}
		}
	}

	return 0;
}