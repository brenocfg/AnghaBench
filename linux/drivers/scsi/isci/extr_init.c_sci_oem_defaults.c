#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct sci_user_parameters {int stp_inactivity_timeout; int ssp_inactivity_timeout; int stp_max_occupancy_timeout; int ssp_max_occupancy_timeout; int no_outbound_task_timeout; TYPE_3__* phys; } ;
struct TYPE_6__ {int max_concurr_spin_up; int do_enable_ssc; scalar_t__ cable_selection_mask; int /*<<< orphan*/  mode_type; } ;
struct sci_oem_params {TYPE_5__* phys; TYPE_2__* ports; TYPE_1__ controller; } ;
struct isci_host {scalar_t__ id; struct sci_oem_params oem_parameters; struct sci_user_parameters user_parameters; } ;
struct TYPE_9__ {int high; scalar_t__ low; } ;
struct TYPE_10__ {TYPE_4__ sas_address; } ;
struct TYPE_8__ {int align_insertion_frequency; int in_connection_align_insertion_frequency; int notify_enable_spin_up_insertion_frequency; int /*<<< orphan*/  max_speed_generation; } ;
struct TYPE_7__ {scalar_t__ phy_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCIC_PORT_AUTOMATIC_CONFIGURATION_MODE ; 
 int /*<<< orphan*/  SCIC_SDS_PARM_GEN2_SPEED ; 
 int SCI_MAX_PHYS ; 
 int SCI_MAX_PORTS ; 

__attribute__((used)) static void sci_oem_defaults(struct isci_host *ihost)
{
	/* these defaults are overridden by the platform / firmware */
	struct sci_user_parameters *user = &ihost->user_parameters;
	struct sci_oem_params *oem = &ihost->oem_parameters;
	int i;

	/* Default to APC mode. */
	oem->controller.mode_type = SCIC_PORT_AUTOMATIC_CONFIGURATION_MODE;

	/* Default to APC mode. */
	oem->controller.max_concurr_spin_up = 1;

	/* Default to no SSC operation. */
	oem->controller.do_enable_ssc = false;

	/* Default to short cables on all phys. */
	oem->controller.cable_selection_mask = 0;

	/* Initialize all of the port parameter information to narrow ports. */
	for (i = 0; i < SCI_MAX_PORTS; i++)
		oem->ports[i].phy_mask = 0;

	/* Initialize all of the phy parameter information. */
	for (i = 0; i < SCI_MAX_PHYS; i++) {
		/* Default to 3G (i.e. Gen 2). */
		user->phys[i].max_speed_generation = SCIC_SDS_PARM_GEN2_SPEED;

		/* the frequencies cannot be 0 */
		user->phys[i].align_insertion_frequency = 0x7f;
		user->phys[i].in_connection_align_insertion_frequency = 0xff;
		user->phys[i].notify_enable_spin_up_insertion_frequency = 0x33;

		/* Previous Vitesse based expanders had a arbitration issue that
		 * is worked around by having the upper 32-bits of SAS address
		 * with a value greater then the Vitesse company identifier.
		 * Hence, usage of 0x5FCFFFFF.
		 */
		oem->phys[i].sas_address.low = 0x1 + ihost->id;
		oem->phys[i].sas_address.high = 0x5FCFFFFF;
	}

	user->stp_inactivity_timeout = 5;
	user->ssp_inactivity_timeout = 5;
	user->stp_max_occupancy_timeout = 5;
	user->ssp_max_occupancy_timeout = 20;
	user->no_outbound_task_timeout = 2;
}