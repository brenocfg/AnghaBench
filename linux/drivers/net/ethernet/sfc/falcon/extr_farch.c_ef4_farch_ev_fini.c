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
struct ef4_nic {TYPE_1__* type; } ;
struct ef4_channel {int /*<<< orphan*/  eventq; int /*<<< orphan*/  channel; struct ef4_nic* efx; } ;
typedef  int /*<<< orphan*/  ef4_oword_t ;
struct TYPE_2__ {int /*<<< orphan*/  evq_ptr_tbl_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  EF4_ZERO_OWORD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ef4_fini_special_buffer (struct ef4_nic*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ef4_writeo_table (struct ef4_nic*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void ef4_farch_ev_fini(struct ef4_channel *channel)
{
	ef4_oword_t reg;
	struct ef4_nic *efx = channel->efx;

	/* Remove event queue from card */
	EF4_ZERO_OWORD(reg);
	ef4_writeo_table(efx, &reg, efx->type->evq_ptr_tbl_base,
			 channel->channel);

	/* Unpin event queue */
	ef4_fini_special_buffer(efx, &channel->eventq);
}