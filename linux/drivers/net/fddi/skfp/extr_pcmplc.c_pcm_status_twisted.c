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
struct TYPE_4__ {scalar_t__ sas; } ;
struct s_smc {TYPE_3__* y; TYPE_1__ s; } ;
struct TYPE_6__ {TYPE_2__* mib; scalar_t__ twisted; } ;
struct TYPE_5__ {scalar_t__ fddiPORTPCMState; } ;

/* Variables and functions */
 size_t PA ; 
 size_t PB ; 
 scalar_t__ PC8_ACTIVE ; 
 scalar_t__ SMT_DAS ; 

int pcm_status_twisted(struct s_smc *smc)
{
	int	twist = 0 ;
	if (smc->s.sas != SMT_DAS)
		return 0;
	if (smc->y[PA].twisted && (smc->y[PA].mib->fddiPORTPCMState == PC8_ACTIVE))
		twist |= 1 ;
	if (smc->y[PB].twisted && (smc->y[PB].mib->fddiPORTPCMState == PC8_ACTIVE))
		twist |= 2 ;
	return twist;
}