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
typedef  size_t u16 ;
struct sci_user_parameters {scalar_t__ stp_inactivity_timeout; scalar_t__ ssp_inactivity_timeout; scalar_t__ stp_max_occupancy_timeout; scalar_t__ ssp_max_occupancy_timeout; scalar_t__ no_outbound_task_timeout; struct sci_phy_user_params* phys; } ;
struct sci_phy_user_params {scalar_t__ max_speed_generation; int in_connection_align_insertion_frequency; scalar_t__ align_insertion_frequency; scalar_t__ notify_enable_spin_up_insertion_frequency; } ;
struct isci_host {int /*<<< orphan*/  user_parameters; } ;
typedef  enum sci_status { ____Placeholder_sci_status } sci_status ;

/* Variables and functions */
 scalar_t__ SCIC_SDS_PARM_MAX_SPEED ; 
 scalar_t__ SCIC_SDS_PARM_NO_SPEED ; 
 int SCI_FAILURE_INVALID_PARAMETER_VALUE ; 
 size_t SCI_MAX_PHYS ; 
 int SCI_SUCCESS ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct sci_user_parameters*,int) ; 

__attribute__((used)) static enum sci_status sci_user_parameters_set(struct isci_host *ihost,
					       struct sci_user_parameters *sci_parms)
{
	u16 index;

	/*
	 * Validate the user parameters.  If they are not legal, then
	 * return a failure.
	 */
	for (index = 0; index < SCI_MAX_PHYS; index++) {
		struct sci_phy_user_params *u;

		u = &sci_parms->phys[index];

		if (!((u->max_speed_generation <= SCIC_SDS_PARM_MAX_SPEED) &&
		      (u->max_speed_generation > SCIC_SDS_PARM_NO_SPEED)))
			return SCI_FAILURE_INVALID_PARAMETER_VALUE;

		if ((u->in_connection_align_insertion_frequency < 3) ||
		    (u->align_insertion_frequency == 0) ||
		    (u->notify_enable_spin_up_insertion_frequency == 0))
			return SCI_FAILURE_INVALID_PARAMETER_VALUE;
	}

	if ((sci_parms->stp_inactivity_timeout == 0) ||
	    (sci_parms->ssp_inactivity_timeout == 0) ||
	    (sci_parms->stp_max_occupancy_timeout == 0) ||
	    (sci_parms->ssp_max_occupancy_timeout == 0) ||
	    (sci_parms->no_outbound_task_timeout == 0))
		return SCI_FAILURE_INVALID_PARAMETER_VALUE;

	memcpy(&ihost->user_parameters, sci_parms, sizeof(*sci_parms));

	return SCI_SUCCESS;
}