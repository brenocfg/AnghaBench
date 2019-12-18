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

/* Variables and functions */
 int /*<<< orphan*/  RESET_TYPE_INVISIBLE ; 
 int /*<<< orphan*/  ef4_schedule_reset (struct ef4_nic*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void falcon_a1_prepare_enable_fc_tx(struct ef4_nic *efx)
{
	/* Schedule a reset to recover */
	ef4_schedule_reset(efx, RESET_TYPE_INVISIBLE);
}