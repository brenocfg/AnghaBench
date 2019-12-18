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
struct ef4_channel {scalar_t__ channel; TYPE_1__* efx; } ;
struct TYPE_2__ {scalar_t__ tx_channel_offset; scalar_t__ n_tx_channels; } ;

/* Variables and functions */

__attribute__((used)) static inline bool ef4_channel_has_tx_queues(struct ef4_channel *channel)
{
	return channel->channel - channel->efx->tx_channel_offset <
		channel->efx->n_tx_channels;
}