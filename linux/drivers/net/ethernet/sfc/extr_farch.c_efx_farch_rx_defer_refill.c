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
struct efx_rx_queue {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EFX_CHANNEL_MAGIC_FILL (struct efx_rx_queue*) ; 
 int /*<<< orphan*/  efx_farch_magic_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efx_rx_queue_channel (struct efx_rx_queue*) ; 

void efx_farch_rx_defer_refill(struct efx_rx_queue *rx_queue)
{
	efx_farch_magic_event(efx_rx_queue_channel(rx_queue),
			      EFX_CHANNEL_MAGIC_FILL(rx_queue));
}