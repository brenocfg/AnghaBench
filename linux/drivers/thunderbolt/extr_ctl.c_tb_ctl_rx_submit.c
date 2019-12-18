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
struct ctl_pkg {int /*<<< orphan*/  frame; TYPE_1__* ctl; } ;
struct TYPE_2__ {int /*<<< orphan*/  rx; } ;

/* Variables and functions */
 int /*<<< orphan*/  tb_ring_rx (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void tb_ctl_rx_submit(struct ctl_pkg *pkg)
{
	tb_ring_rx(pkg->ctl->rx, &pkg->frame); /*
					     * We ignore failures during stop.
					     * All rx packets are referenced
					     * from ctl->rx_packets, so we do
					     * not loose them.
					     */
}