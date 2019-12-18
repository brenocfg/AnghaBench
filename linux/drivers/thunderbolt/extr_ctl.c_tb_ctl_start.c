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
struct tb_ctl {int running; int /*<<< orphan*/ * rx_packets; int /*<<< orphan*/  rx; int /*<<< orphan*/  tx; } ;

/* Variables and functions */
 int TB_CTL_RX_PKG_COUNT ; 
 int /*<<< orphan*/  tb_ctl_dbg (struct tb_ctl*,char*) ; 
 int /*<<< orphan*/  tb_ctl_rx_submit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tb_ring_start (int /*<<< orphan*/ ) ; 

void tb_ctl_start(struct tb_ctl *ctl)
{
	int i;
	tb_ctl_dbg(ctl, "control channel starting...\n");
	tb_ring_start(ctl->tx); /* is used to ack hotplug packets, start first */
	tb_ring_start(ctl->rx);
	for (i = 0; i < TB_CTL_RX_PKG_COUNT; i++)
		tb_ctl_rx_submit(ctl->rx_packets[i]);

	ctl->running = true;
}