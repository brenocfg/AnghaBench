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
struct TYPE_2__ {int /*<<< orphan*/  count_max; int /*<<< orphan*/  head; } ;
union ep_buffer_info {TYPE_1__ v1i; } ;
struct epbuf_handler {union ep_buffer_info* info; } ;

/* Variables and functions */
 int /*<<< orphan*/  EP_RING_INDEX_INC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ fjes_hw_epbuf_rx_is_empty (struct epbuf_handler*) ; 

void fjes_hw_epbuf_rx_curpkt_drop(struct epbuf_handler *epbh)
{
	union ep_buffer_info *info = epbh->info;

	if (fjes_hw_epbuf_rx_is_empty(epbh))
		return;

	EP_RING_INDEX_INC(epbh->info->v1i.head, info->v1i.count_max);
}