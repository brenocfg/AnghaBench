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
struct efx_nic {int irq_mod_step_us; int irq_rx_moderation_us; TYPE_1__* type; } ;
struct efx_channel {scalar_t__ irq_mod_score; int irq_moderation_us; scalar_t__ irq_count; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* push_irq_moderation ) (struct efx_channel*) ;} ;

/* Variables and functions */
 scalar_t__ irq_adapt_high_thresh ; 
 scalar_t__ irq_adapt_low_thresh ; 
 int /*<<< orphan*/  stub1 (struct efx_channel*) ; 
 int /*<<< orphan*/  stub2 (struct efx_channel*) ; 

__attribute__((used)) static void efx_update_irq_mod(struct efx_nic *efx, struct efx_channel *channel)
{
	int step = efx->irq_mod_step_us;

	if (channel->irq_mod_score < irq_adapt_low_thresh) {
		if (channel->irq_moderation_us > step) {
			channel->irq_moderation_us -= step;
			efx->type->push_irq_moderation(channel);
		}
	} else if (channel->irq_mod_score > irq_adapt_high_thresh) {
		if (channel->irq_moderation_us <
		    efx->irq_rx_moderation_us) {
			channel->irq_moderation_us += step;
			efx->type->push_irq_moderation(channel);
		}
	}

	channel->irq_count = 0;
	channel->irq_mod_score = 0;
}