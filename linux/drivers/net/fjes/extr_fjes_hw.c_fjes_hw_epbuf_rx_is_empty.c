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
struct TYPE_2__ {int rx_status; scalar_t__ count_max; int /*<<< orphan*/  tail; int /*<<< orphan*/  head; } ;
union ep_buffer_info {TYPE_1__ v1i; } ;
struct epbuf_handler {union ep_buffer_info* info; } ;

/* Variables and functions */
 int EP_RING_EMPTY (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int FJES_RX_MTU_CHANGING_DONE ; 

bool fjes_hw_epbuf_rx_is_empty(struct epbuf_handler *epbh)
{
	union ep_buffer_info *info = epbh->info;

	if (!(info->v1i.rx_status & FJES_RX_MTU_CHANGING_DONE))
		return true;

	if (info->v1i.count_max == 0)
		return true;

	return EP_RING_EMPTY(info->v1i.head, info->v1i.tail,
			     info->v1i.count_max);
}