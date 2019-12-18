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
struct TYPE_2__ {scalar_t__ curr; scalar_t__ filled; scalar_t__ dirty; } ;
struct velocity_info {TYPE_1__ rx; } ;

/* Variables and functions */

__attribute__((used)) static void velocity_init_rx_ring_indexes(struct velocity_info *vptr)
{
	vptr->rx.dirty = vptr->rx.filled = vptr->rx.curr = 0;
}