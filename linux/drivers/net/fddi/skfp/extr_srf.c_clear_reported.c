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
struct s_srf_evc {scalar_t__* evc_cond_state; scalar_t__* evc_multiple; scalar_t__ evc_rep_required; int /*<<< orphan*/  evc_code; } ;
struct TYPE_2__ {scalar_t__ any_report; } ;
struct s_smc {TYPE_1__ srf; struct s_srf_evc* evcs; } ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 unsigned int MAX_EVCS ; 
 scalar_t__ SMT_IS_CONDITION (int /*<<< orphan*/ ) ; 
 scalar_t__ TRUE ; 

__attribute__((used)) static void clear_reported(struct s_smc *smc)
{
	struct s_srf_evc	*evc ;
	unsigned int		i ;

	smc->srf.any_report = FALSE ;
	for (i = 0, evc = smc->evcs ; i < MAX_EVCS ; i++, evc++) {
		if (SMT_IS_CONDITION(evc->evc_code)) {
			if (*evc->evc_cond_state == FALSE)
				evc->evc_rep_required = FALSE ;
			else
				smc->srf.any_report = TRUE ;
		}
		else {
			evc->evc_rep_required = FALSE ;
			*evc->evc_multiple = FALSE ;
		}
	}
}