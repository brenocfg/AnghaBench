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
struct s_srf_evc {int evc_code; int evc_index; } ;
struct s_smc {struct s_srf_evc* evcs; } ;

/* Variables and functions */
 unsigned int MAX_EVCS ; 

__attribute__((used)) static struct s_srf_evc *smt_get_evc(struct s_smc *smc, int code, int index)
{
	unsigned int		i ;
	struct s_srf_evc	*evc ;

	for (i = 0, evc = smc->evcs ; i < MAX_EVCS ; i++, evc++) {
		if (evc->evc_code == code && evc->evc_index == index)
			return evc;
	}
	return NULL;
}