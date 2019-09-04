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
typedef  int u32 ;
struct uli526x_board_info {scalar_t__ tx_packet_cnt; int cr6_data; struct tx_desc* tx_remove_ptr; int /*<<< orphan*/  tx_jabber_timeout; int /*<<< orphan*/  tx_loss_carrier; int /*<<< orphan*/  tx_no_carrier; int /*<<< orphan*/  tx_late_collision; int /*<<< orphan*/  tx_excessive_collision; int /*<<< orphan*/  ioaddr; int /*<<< orphan*/  tx_fifo_underrun; } ;
struct tx_desc {struct tx_desc* next_tx_desc; int /*<<< orphan*/  tdes1; int /*<<< orphan*/  tdes0; } ;
struct TYPE_2__ {int collisions; int tx_bytes; int /*<<< orphan*/  tx_errors; int /*<<< orphan*/  tx_packets; } ;
struct net_device {TYPE_1__ stats; } ;

/* Variables and functions */
 int CR6_SFT ; 
 int TDES0_ERR_MASK ; 
 scalar_t__ TX_WAKE_DESC_CNT ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int /*<<< orphan*/  update_cr6 (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void uli526x_free_tx_pkt(struct net_device *dev,
				struct uli526x_board_info * db)
{
	struct tx_desc *txptr;
	u32 tdes0;

	txptr = db->tx_remove_ptr;
	while(db->tx_packet_cnt) {
		tdes0 = le32_to_cpu(txptr->tdes0);
		if (tdes0 & 0x80000000)
			break;

		/* A packet sent completed */
		db->tx_packet_cnt--;
		dev->stats.tx_packets++;

		/* Transmit statistic counter */
		if ( tdes0 != 0x7fffffff ) {
			dev->stats.collisions += (tdes0 >> 3) & 0xf;
			dev->stats.tx_bytes += le32_to_cpu(txptr->tdes1) & 0x7ff;
			if (tdes0 & TDES0_ERR_MASK) {
				dev->stats.tx_errors++;
				if (tdes0 & 0x0002) {	/* UnderRun */
					db->tx_fifo_underrun++;
					if ( !(db->cr6_data & CR6_SFT) ) {
						db->cr6_data = db->cr6_data | CR6_SFT;
						update_cr6(db->cr6_data, db->ioaddr);
					}
				}
				if (tdes0 & 0x0100)
					db->tx_excessive_collision++;
				if (tdes0 & 0x0200)
					db->tx_late_collision++;
				if (tdes0 & 0x0400)
					db->tx_no_carrier++;
				if (tdes0 & 0x0800)
					db->tx_loss_carrier++;
				if (tdes0 & 0x4000)
					db->tx_jabber_timeout++;
			}
		}

    		txptr = txptr->next_tx_desc;
	}/* End of while */

	/* Update TX remove pointer to next */
	db->tx_remove_ptr = txptr;

	/* Resource available check */
	if ( db->tx_packet_cnt < TX_WAKE_DESC_CNT )
		netif_wake_queue(dev);	/* Active upper layer, send again */
}