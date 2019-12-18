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
struct tda_state {int dummy; } ;

/* Variables and functions */
 int CalcRFFilterCurve (struct tda_state*) ; 
 int FixedContentsI2CUpdate (struct tda_state*) ; 
 int StandBy (struct tda_state*) ; 

__attribute__((used)) static int InitCal(struct tda_state *state)
{
	int status = 0;

	do {
		status = FixedContentsI2CUpdate(state);
		if (status < 0)
			break;
		status = CalcRFFilterCurve(state);
		if (status < 0)
			break;
		status = StandBy(state);
		if (status < 0)
			break;
		/* m_bInitDone = true; */
	} while (0);
	return status;
}