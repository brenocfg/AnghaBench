#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char dstat; } ;
struct TYPE_4__ {TYPE_1__ cmd; } ;
struct irb {TYPE_2__ scsw; } ;
struct dasd_device {int dummy; } ;
struct dasd_ccw_req {int dummy; } ;

/* Variables and functions */
 char DEV_STAT_ATTENTION ; 
 char DEV_STAT_DEV_END ; 
 char DEV_STAT_UNIT_EXCEP ; 
 int /*<<< orphan*/  dasd_generic_handle_state_change (struct dasd_device*) ; 

__attribute__((used)) static void dasd_fba_check_for_device_change(struct dasd_device *device,
					     struct dasd_ccw_req *cqr,
					     struct irb *irb)
{
	char mask;

	/* first of all check for state change pending interrupt */
	mask = DEV_STAT_ATTENTION | DEV_STAT_DEV_END | DEV_STAT_UNIT_EXCEP;
	if ((irb->scsw.cmd.dstat & mask) == mask)
		dasd_generic_handle_state_change(device);
}