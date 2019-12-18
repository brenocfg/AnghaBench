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
struct fcoe_ctlr {int /*<<< orphan*/  flogi_oxid; scalar_t__ sol_time; scalar_t__ port_ka_time; scalar_t__ ctlr_ka_time; int /*<<< orphan*/  timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  FC_XID_UNKNOWN ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fcoe_ctlr_map_dest (struct fcoe_ctlr*) ; 
 int /*<<< orphan*/  fcoe_ctlr_reset_fcfs (struct fcoe_ctlr*) ; 

__attribute__((used)) static void fcoe_ctlr_reset(struct fcoe_ctlr *fip)
{
	fcoe_ctlr_reset_fcfs(fip);
	del_timer(&fip->timer);
	fip->ctlr_ka_time = 0;
	fip->port_ka_time = 0;
	fip->sol_time = 0;
	fip->flogi_oxid = FC_XID_UNKNOWN;
	fcoe_ctlr_map_dest(fip);
}