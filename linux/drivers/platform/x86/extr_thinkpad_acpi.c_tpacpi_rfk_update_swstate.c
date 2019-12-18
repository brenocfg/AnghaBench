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
struct tpacpi_rfk {int /*<<< orphan*/  rfkill; TYPE_1__* ops; } ;
struct TYPE_2__ {int (* get_status ) () ;} ;

/* Variables and functions */
 int ENODEV ; 
 int TPACPI_RFK_RADIO_OFF ; 
 int /*<<< orphan*/  rfkill_set_sw_state (int /*<<< orphan*/ ,int) ; 
 int stub1 () ; 

__attribute__((used)) static int tpacpi_rfk_update_swstate(const struct tpacpi_rfk *tp_rfk)
{
	int status;

	if (!tp_rfk)
		return -ENODEV;

	status = (tp_rfk->ops->get_status)();
	if (status < 0)
		return status;

	rfkill_set_sw_state(tp_rfk->rfkill,
			    (status == TPACPI_RFK_RADIO_OFF));

	return status;
}