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
struct stfsm {scalar_t__ reset_por; TYPE_1__* info; scalar_t__ reset_signal; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int FLASH_FLAG_RESET ; 

__attribute__((used)) static bool stfsm_can_handle_soc_reset(struct stfsm *fsm)
{
	/* Reset signal is available on the board and supported by the device */
	if (fsm->reset_signal && fsm->info->flags & FLASH_FLAG_RESET)
		return true;

	/* Board-level logic forces a power-on-reset */
	if (fsm->reset_por)
		return true;

	/* Reset is not properly handled and may result in failure to reboot */
	return false;
}