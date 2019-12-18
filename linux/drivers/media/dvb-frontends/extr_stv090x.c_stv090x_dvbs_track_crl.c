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
struct stv090x_state {int srate; TYPE_1__* internal; } ;
struct TYPE_2__ {int dev_ver; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACLC ; 
 int /*<<< orphan*/  BCLC ; 
 int /*<<< orphan*/  FE_ERROR ; 
 scalar_t__ STV090x_WRITE_DEMOD (struct stv090x_state*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,int,char*) ; 

__attribute__((used)) static int stv090x_dvbs_track_crl(struct stv090x_state *state)
{
	if (state->internal->dev_ver >= 0x30) {
		/* Set ACLC BCLC optimised value vs SR */
		if (state->srate >= 15000000) {
			if (STV090x_WRITE_DEMOD(state, ACLC, 0x2b) < 0)
				goto err;
			if (STV090x_WRITE_DEMOD(state, BCLC, 0x1a) < 0)
				goto err;
		} else if ((state->srate >= 7000000) && (15000000 > state->srate)) {
			if (STV090x_WRITE_DEMOD(state, ACLC, 0x0c) < 0)
				goto err;
			if (STV090x_WRITE_DEMOD(state, BCLC, 0x1b) < 0)
				goto err;
		} else if (state->srate < 7000000) {
			if (STV090x_WRITE_DEMOD(state, ACLC, 0x2c) < 0)
				goto err;
			if (STV090x_WRITE_DEMOD(state, BCLC, 0x1c) < 0)
				goto err;
		}

	} else {
		/* Cut 2.0 */
		if (STV090x_WRITE_DEMOD(state, ACLC, 0x1a) < 0)
			goto err;
		if (STV090x_WRITE_DEMOD(state, BCLC, 0x09) < 0)
			goto err;
	}
	return 0;
err:
	dprintk(FE_ERROR, 1, "I/O error");
	return -1;
}