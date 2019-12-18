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
struct ef4_nic {int dummy; } ;
struct ef4_channel {int /*<<< orphan*/  channel; int /*<<< orphan*/  irq_moderation_us; struct ef4_nic* efx; } ;
typedef  int /*<<< orphan*/  ef4_dword_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int /*<<< orphan*/  EF4_POPULATE_DWORD_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  FFE_BB_TIMER_MODE_DIS ; 
 int /*<<< orphan*/  FFE_BB_TIMER_MODE_INT_HLDOFF ; 
 int /*<<< orphan*/  FRF_AB_TC_TIMER_MODE ; 
 int /*<<< orphan*/  FRF_AB_TC_TIMER_VAL ; 
 scalar_t__ FR_AA_TIMER_COMMAND_KER ; 
 scalar_t__ FR_BZ_TIMER_COMMAND_P0 ; 
 unsigned int ef4_usecs_to_ticks (struct ef4_nic*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ef4_writed_page_locked (struct ef4_nic*,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void falcon_push_irq_moderation(struct ef4_channel *channel)
{
	ef4_dword_t timer_cmd;
	struct ef4_nic *efx = channel->efx;

	/* Set timer register */
	if (channel->irq_moderation_us) {
		unsigned int ticks;

		ticks = ef4_usecs_to_ticks(efx, channel->irq_moderation_us);
		EF4_POPULATE_DWORD_2(timer_cmd,
				     FRF_AB_TC_TIMER_MODE,
				     FFE_BB_TIMER_MODE_INT_HLDOFF,
				     FRF_AB_TC_TIMER_VAL,
				     ticks - 1);
	} else {
		EF4_POPULATE_DWORD_2(timer_cmd,
				     FRF_AB_TC_TIMER_MODE,
				     FFE_BB_TIMER_MODE_DIS,
				     FRF_AB_TC_TIMER_VAL, 0);
	}
	BUILD_BUG_ON(FR_AA_TIMER_COMMAND_KER != FR_BZ_TIMER_COMMAND_P0);
	ef4_writed_page_locked(efx, &timer_cmd, FR_BZ_TIMER_COMMAND_P0,
			       channel->channel);
}