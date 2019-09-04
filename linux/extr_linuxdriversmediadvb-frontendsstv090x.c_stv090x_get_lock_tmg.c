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
struct stv090x_state {int algo; int srate; int DemodTimeout; int FecTimeout; } ;

/* Variables and functions */
 int /*<<< orphan*/  FE_DEBUG ; 
#define  STV090x_BLIND_SEARCH 130 
#define  STV090x_COLD_SEARCH 129 
#define  STV090x_WARM_SEARCH 128 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,int,char*) ; 

__attribute__((used)) static void stv090x_get_lock_tmg(struct stv090x_state *state)
{
	switch (state->algo) {
	case STV090x_BLIND_SEARCH:
		dprintk(FE_DEBUG, 1, "Blind Search");
		if (state->srate <= 1500000) {  /*10Msps< SR <=15Msps*/
			state->DemodTimeout = 1500;
			state->FecTimeout = 400;
		} else if (state->srate <= 5000000) {  /*10Msps< SR <=15Msps*/
			state->DemodTimeout = 1000;
			state->FecTimeout = 300;
		} else {  /*SR >20Msps*/
			state->DemodTimeout = 700;
			state->FecTimeout = 100;
		}
		break;

	case STV090x_COLD_SEARCH:
	case STV090x_WARM_SEARCH:
	default:
		dprintk(FE_DEBUG, 1, "Normal Search");
		if (state->srate <= 1000000) {  /*SR <=1Msps*/
			state->DemodTimeout = 4500;
			state->FecTimeout = 1700;
		} else if (state->srate <= 2000000) { /*1Msps < SR <= 2Msps */
			state->DemodTimeout = 2500;
			state->FecTimeout = 1100;
		} else if (state->srate <= 5000000) { /*2Msps < SR <= 5Msps */
			state->DemodTimeout = 1000;
			state->FecTimeout = 550;
		} else if (state->srate <= 10000000) { /*5Msps < SR <= 10Msps */
			state->DemodTimeout = 700;
			state->FecTimeout = 250;
		} else if (state->srate <= 20000000) { /*10Msps < SR <= 20Msps */
			state->DemodTimeout = 400;
			state->FecTimeout = 130;
		} else {   /*SR >20Msps*/
			state->DemodTimeout = 300;
			state->FecTimeout = 100;
		}
		break;
	}

	if (state->algo == STV090x_WARM_SEARCH)
		state->DemodTimeout /= 2;
}