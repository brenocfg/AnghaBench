#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct device_node {int dummy; } ;
struct TYPE_6__ {scalar_t__ type; } ;
struct TYPE_5__ {int board_flags; } ;

/* Variables and functions */
 long EPERM ; 
 int PMAC_MB_CAN_SLEEP ; 
 int /*<<< orphan*/  heathrow_sleep (TYPE_2__*,int) ; 
 int /*<<< orphan*/  heathrow_wakeup (TYPE_2__*,int) ; 
 TYPE_2__* macio_chips ; 
 scalar_t__ macio_gatwick ; 
 TYPE_1__ pmac_mb ; 

__attribute__((used)) static long heathrow_sleep_state(struct device_node *node, long param,
				 long value)
{
	if ((pmac_mb.board_flags & PMAC_MB_CAN_SLEEP) == 0)
		return -EPERM;
	if (value == 1) {
		if (macio_chips[1].type == macio_gatwick)
			heathrow_sleep(&macio_chips[0], 1);
		heathrow_sleep(&macio_chips[0], 0);
	} else if (value == 0) {
		heathrow_wakeup(&macio_chips[0], 0);
		if (macio_chips[1].type == macio_gatwick)
			heathrow_wakeup(&macio_chips[0], 1);
	}
	return 0;
}