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
struct hci_uart {TYPE_2__* hdev; struct h5* priv; } ;
struct h5 {scalar_t__ tx_ack; scalar_t__ state; int /*<<< orphan*/  rx_pending; int /*<<< orphan*/  rx_func; TYPE_1__* rx_skb; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;
struct TYPE_3__ {unsigned char* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BT_ERR (char*,...) ; 
 scalar_t__ H5_ACTIVE ; 
 int /*<<< orphan*/  H5_HDR_ACK (unsigned char const*) ; 
 int /*<<< orphan*/  H5_HDR_CRC (unsigned char const*) ; 
 int /*<<< orphan*/  H5_HDR_LEN (unsigned char const*) ; 
 scalar_t__ H5_HDR_PKT_TYPE (unsigned char const*) ; 
 scalar_t__ H5_HDR_RELIABLE (unsigned char const*) ; 
 scalar_t__ H5_HDR_SEQ (unsigned char const*) ; 
 scalar_t__ HCI_3WIRE_LINK_PKT ; 
 int /*<<< orphan*/  h5_reset_rx (struct h5*) ; 
 int /*<<< orphan*/  h5_rx_payload ; 

__attribute__((used)) static int h5_rx_3wire_hdr(struct hci_uart *hu, unsigned char c)
{
	struct h5 *h5 = hu->priv;
	const unsigned char *hdr = h5->rx_skb->data;

	BT_DBG("%s rx: seq %u ack %u crc %u rel %u type %u len %u",
	       hu->hdev->name, H5_HDR_SEQ(hdr), H5_HDR_ACK(hdr),
	       H5_HDR_CRC(hdr), H5_HDR_RELIABLE(hdr), H5_HDR_PKT_TYPE(hdr),
	       H5_HDR_LEN(hdr));

	if (((hdr[0] + hdr[1] + hdr[2] + hdr[3]) & 0xff) != 0xff) {
		BT_ERR("Invalid header checksum");
		h5_reset_rx(h5);
		return 0;
	}

	if (H5_HDR_RELIABLE(hdr) && H5_HDR_SEQ(hdr) != h5->tx_ack) {
		BT_ERR("Out-of-order packet arrived (%u != %u)",
		       H5_HDR_SEQ(hdr), h5->tx_ack);
		h5_reset_rx(h5);
		return 0;
	}

	if (h5->state != H5_ACTIVE &&
	    H5_HDR_PKT_TYPE(hdr) != HCI_3WIRE_LINK_PKT) {
		BT_ERR("Non-link packet received in non-active state");
		h5_reset_rx(h5);
		return 0;
	}

	h5->rx_func = h5_rx_payload;
	h5->rx_pending = H5_HDR_LEN(hdr);

	return 0;
}