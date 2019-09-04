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
struct hci_uart {struct h5* priv; } ;
struct h5 {int rx_pending; int /*<<< orphan*/  rx_func; TYPE_1__* rx_skb; } ;
struct TYPE_2__ {unsigned char* data; } ;

/* Variables and functions */
 scalar_t__ H5_HDR_CRC (unsigned char const*) ; 
 int /*<<< orphan*/  h5_complete_rx_pkt (struct hci_uart*) ; 
 int /*<<< orphan*/  h5_rx_crc ; 

__attribute__((used)) static int h5_rx_payload(struct hci_uart *hu, unsigned char c)
{
	struct h5 *h5 = hu->priv;
	const unsigned char *hdr = h5->rx_skb->data;

	if (H5_HDR_CRC(hdr)) {
		h5->rx_func = h5_rx_crc;
		h5->rx_pending = 2;
	} else {
		h5_complete_rx_pkt(hu);
	}

	return 0;
}