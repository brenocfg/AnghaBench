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
struct TYPE_2__ {scalar_t__ core_index; } ;
struct ef4_channel {TYPE_1__ rx_queue; } ;

/* Variables and functions */

__attribute__((used)) static inline bool ef4_channel_has_rx_queue(struct ef4_channel *channel)
{
	return channel->rx_queue.core_index >= 0;
}