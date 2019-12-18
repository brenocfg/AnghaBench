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
struct TYPE_2__ {int /*<<< orphan*/  rx_length_errors; int /*<<< orphan*/  rx_frame_errors; int /*<<< orphan*/  rx_crc_errors; int /*<<< orphan*/  rx_fifo_errors; int /*<<< orphan*/  rx_errors; } ;
struct net_device {TYPE_1__ stats; } ;
struct fst_port_info {unsigned short index; } ;
struct fst_card_info {unsigned short card_no; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_ASS ; 
 unsigned char RX_CRC ; 
 unsigned char RX_ENP ; 
 unsigned char RX_FRAM ; 
 unsigned char RX_OFLO ; 
 unsigned char RX_STP ; 
 int /*<<< orphan*/  dbg (int /*<<< orphan*/ ,char*,unsigned short,unsigned short,...) ; 
 struct net_device* port_to_dev (struct fst_port_info*) ; 

__attribute__((used)) static void
fst_log_rx_error(struct fst_card_info *card, struct fst_port_info *port,
		 unsigned char dmabits, int rxp, unsigned short len)
{
	struct net_device *dev = port_to_dev(port);

	/*
	 * Increment the appropriate error counter
	 */
	dev->stats.rx_errors++;
	if (dmabits & RX_OFLO) {
		dev->stats.rx_fifo_errors++;
		dbg(DBG_ASS, "Rx fifo error on card %d port %d buffer %d\n",
		    card->card_no, port->index, rxp);
	}
	if (dmabits & RX_CRC) {
		dev->stats.rx_crc_errors++;
		dbg(DBG_ASS, "Rx crc error on card %d port %d\n",
		    card->card_no, port->index);
	}
	if (dmabits & RX_FRAM) {
		dev->stats.rx_frame_errors++;
		dbg(DBG_ASS, "Rx frame error on card %d port %d\n",
		    card->card_no, port->index);
	}
	if (dmabits == (RX_STP | RX_ENP)) {
		dev->stats.rx_length_errors++;
		dbg(DBG_ASS, "Rx length error (%d) on card %d port %d\n",
		    len, card->card_no, port->index);
	}
}