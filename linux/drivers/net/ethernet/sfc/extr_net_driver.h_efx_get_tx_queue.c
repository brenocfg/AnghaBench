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
struct efx_tx_queue {int dummy; } ;
struct efx_nic {unsigned int n_tx_channels; unsigned int tx_channel_offset; TYPE_1__** channel; } ;
struct TYPE_2__ {struct efx_tx_queue* tx_queue; } ;

/* Variables and functions */
 unsigned int EFX_TXQ_TYPES ; 
 int /*<<< orphan*/  EFX_WARN_ON_ONCE_PARANOID (int) ; 

__attribute__((used)) static inline struct efx_tx_queue *
efx_get_tx_queue(struct efx_nic *efx, unsigned index, unsigned type)
{
	EFX_WARN_ON_ONCE_PARANOID(index >= efx->n_tx_channels ||
				  type >= EFX_TXQ_TYPES);
	return &efx->channel[efx->tx_channel_offset + index]->tx_queue[type];
}