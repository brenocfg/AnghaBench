#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct timer_list {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  opcode; } ;
struct TYPE_5__ {TYPE_1__ cmd; } ;
struct TYPE_6__ {TYPE_2__ srp; } ;
struct srp_event_struct {TYPE_3__ iu; struct ibmvscsi_host_data* hostdata; } ;
struct ibmvscsi_host_data {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct srp_event_struct* evt_struct ; 
 struct srp_event_struct* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ibmvscsi_reset_host (struct ibmvscsi_host_data*) ; 
 int /*<<< orphan*/  timer ; 

__attribute__((used)) static void ibmvscsi_timeout(struct timer_list *t)
{
	struct srp_event_struct *evt_struct = from_timer(evt_struct, t, timer);
	struct ibmvscsi_host_data *hostdata = evt_struct->hostdata;

	dev_err(hostdata->dev, "Command timed out (%x). Resetting connection\n",
		evt_struct->iu.srp.cmd.opcode);

	ibmvscsi_reset_host(hostdata);
}