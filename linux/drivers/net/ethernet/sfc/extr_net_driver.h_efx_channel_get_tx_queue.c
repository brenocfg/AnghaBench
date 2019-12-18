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
struct efx_tx_queue {int dummy; } ;
struct efx_channel {struct efx_tx_queue* tx_queue; } ;

/* Variables and functions */
 unsigned int EFX_TXQ_TYPES ; 
 int /*<<< orphan*/  EFX_WARN_ON_ONCE_PARANOID (int) ; 
 int /*<<< orphan*/  efx_channel_has_tx_queues (struct efx_channel*) ; 

__attribute__((used)) static inline struct efx_tx_queue *
efx_channel_get_tx_queue(struct efx_channel *channel, unsigned type)
{
	EFX_WARN_ON_ONCE_PARANOID(!efx_channel_has_tx_queues(channel) ||
				  type >= EFX_TXQ_TYPES);
	return &channel->tx_queue[type];
}