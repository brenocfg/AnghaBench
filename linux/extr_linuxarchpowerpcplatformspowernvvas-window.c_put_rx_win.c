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
struct vas_window {int /*<<< orphan*/  num_txwins; int /*<<< orphan*/  tx_win; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void put_rx_win(struct vas_window *rxwin)
{
	/* Better not be a send window! */
	WARN_ON_ONCE(rxwin->tx_win);

	atomic_dec(&rxwin->num_txwins);
}