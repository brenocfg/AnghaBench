#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  rsvd_1; } ;
struct TYPE_6__ {TYPE_1__ b; } ;
struct event_arg {TYPE_2__ id; } ;
struct TYPE_7__ {int disc_state; int /*<<< orphan*/  vha; TYPE_2__ d_id; scalar_t__ scan_needed; } ;
typedef  TYPE_3__ fc_port_t ;
typedef  int /*<<< orphan*/  ea ;

/* Variables and functions */
#define  DSC_DELETE_PEND 128 
 int /*<<< orphan*/  RSCN_PORT_ADDR ; 
 int /*<<< orphan*/  memset (struct event_arg*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qla2x00_handle_rscn (int /*<<< orphan*/ ,struct event_arg*) ; 

void qla_rscn_replay(fc_port_t *fcport)
{
	struct event_arg ea;

	switch (fcport->disc_state) {
	case DSC_DELETE_PEND:
		return;
	default:
		break;
	}

	if (fcport->scan_needed) {
		memset(&ea, 0, sizeof(ea));
		ea.id = fcport->d_id;
		ea.id.b.rsvd_1 = RSCN_PORT_ADDR;
		qla2x00_handle_rscn(fcport->vha, &ea);
	}
}