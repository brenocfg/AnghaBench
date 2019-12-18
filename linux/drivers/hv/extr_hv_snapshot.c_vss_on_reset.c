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
struct TYPE_2__ {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  HVUTIL_DEVICE_INIT ; 
 int /*<<< orphan*/  HV_E_FAIL ; 
 scalar_t__ cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vss_respond_to_host (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vss_timeout_work ; 
 TYPE_1__ vss_transaction ; 

__attribute__((used)) static void vss_on_reset(void)
{
	if (cancel_delayed_work_sync(&vss_timeout_work))
		vss_respond_to_host(HV_E_FAIL);
	vss_transaction.state = HVUTIL_DEVICE_INIT;
}