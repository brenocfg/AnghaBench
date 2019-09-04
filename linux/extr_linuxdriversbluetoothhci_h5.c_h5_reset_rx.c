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
struct h5 {int /*<<< orphan*/  flags; scalar_t__ rx_pending; int /*<<< orphan*/  rx_func; int /*<<< orphan*/ * rx_skb; } ;

/* Variables and functions */
 int /*<<< orphan*/  H5_RX_ESC ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h5_rx_delimiter ; 
 int /*<<< orphan*/  kfree_skb (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void h5_reset_rx(struct h5 *h5)
{
	if (h5->rx_skb) {
		kfree_skb(h5->rx_skb);
		h5->rx_skb = NULL;
	}

	h5->rx_func = h5_rx_delimiter;
	h5->rx_pending = 0;
	clear_bit(H5_RX_ESC, &h5->flags);
}