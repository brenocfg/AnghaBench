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
struct efx_nic {TYPE_1__* type; int /*<<< orphan*/  net_dev; } ;
struct efx_channel {int eventq_init; scalar_t__ eventq_read_ptr; int /*<<< orphan*/  channel; struct efx_nic* efx; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* push_irq_moderation ) (struct efx_channel*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  EFX_WARN_ON_PARANOID (int) ; 
 int /*<<< orphan*/  drv ; 
 int efx_nic_init_eventq (struct efx_channel*) ; 
 int /*<<< orphan*/  netif_dbg (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct efx_channel*) ; 

__attribute__((used)) static int efx_init_eventq(struct efx_channel *channel)
{
	struct efx_nic *efx = channel->efx;
	int rc;

	EFX_WARN_ON_PARANOID(channel->eventq_init);

	netif_dbg(efx, drv, efx->net_dev,
		  "chan %d init event queue\n", channel->channel);

	rc = efx_nic_init_eventq(channel);
	if (rc == 0) {
		efx->type->push_irq_moderation(channel);
		channel->eventq_read_ptr = 0;
		channel->eventq_init = true;
	}
	return rc;
}