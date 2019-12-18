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
struct s_smc {int /*<<< orphan*/ * y; } ;

/* Variables and functions */
 int NUMPHYS ; 
 int /*<<< orphan*/  lem_evaluate (struct s_smc*,int /*<<< orphan*/ *) ; 

void sm_lem_evaluate(struct s_smc *smc)
{
	int np ;

	for (np = 0 ; np < NUMPHYS ; np++)
		lem_evaluate(smc,&smc->y[np]) ;
}