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
typedef  int /*<<< orphan*/  u32 ;
struct rxdone_entry_desc {int /*<<< orphan*/  dev_flags; void* size; void* rssi; void* signal; int /*<<< orphan*/  flags; } ;
struct queue_entry_priv_mmio {int /*<<< orphan*/  desc; } ;
struct queue_entry {TYPE_2__* queue; struct queue_entry_priv_mmio* priv_data; } ;
struct TYPE_4__ {TYPE_1__* rt2x00dev; } ;
struct TYPE_3__ {void* rssi_offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  RXDONE_MY_BSS ; 
 int /*<<< orphan*/  RXDONE_SIGNAL_BITRATE ; 
 int /*<<< orphan*/  RXDONE_SIGNAL_PLCP ; 
 int /*<<< orphan*/  RXD_W0_CRC_ERROR ; 
 int /*<<< orphan*/  RXD_W0_DATABYTE_COUNT ; 
 int /*<<< orphan*/  RXD_W0_MY_BSS ; 
 int /*<<< orphan*/  RXD_W0_OFDM ; 
 int /*<<< orphan*/  RXD_W0_PHYSICAL_ERROR ; 
 int /*<<< orphan*/  RXD_W2_RSSI ; 
 int /*<<< orphan*/  RXD_W2_SIGNAL ; 
 int /*<<< orphan*/  RX_FLAG_FAILED_FCS_CRC ; 
 int /*<<< orphan*/  RX_FLAG_FAILED_PLCP_CRC ; 
 int /*<<< orphan*/  rt2x00_desc_read (int /*<<< orphan*/ ,int) ; 
 void* rt2x00_get_field32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rt2500pci_fill_rxdone(struct queue_entry *entry,
				  struct rxdone_entry_desc *rxdesc)
{
	struct queue_entry_priv_mmio *entry_priv = entry->priv_data;
	u32 word0;
	u32 word2;

	word0 = rt2x00_desc_read(entry_priv->desc, 0);
	word2 = rt2x00_desc_read(entry_priv->desc, 2);

	if (rt2x00_get_field32(word0, RXD_W0_CRC_ERROR))
		rxdesc->flags |= RX_FLAG_FAILED_FCS_CRC;
	if (rt2x00_get_field32(word0, RXD_W0_PHYSICAL_ERROR))
		rxdesc->flags |= RX_FLAG_FAILED_PLCP_CRC;

	/*
	 * Obtain the status about this packet.
	 * When frame was received with an OFDM bitrate,
	 * the signal is the PLCP value. If it was received with
	 * a CCK bitrate the signal is the rate in 100kbit/s.
	 */
	rxdesc->signal = rt2x00_get_field32(word2, RXD_W2_SIGNAL);
	rxdesc->rssi = rt2x00_get_field32(word2, RXD_W2_RSSI) -
	    entry->queue->rt2x00dev->rssi_offset;
	rxdesc->size = rt2x00_get_field32(word0, RXD_W0_DATABYTE_COUNT);

	if (rt2x00_get_field32(word0, RXD_W0_OFDM))
		rxdesc->dev_flags |= RXDONE_SIGNAL_PLCP;
	else
		rxdesc->dev_flags |= RXDONE_SIGNAL_BITRATE;
	if (rt2x00_get_field32(word0, RXD_W0_MY_BSS))
		rxdesc->dev_flags |= RXDONE_MY_BSS;
}