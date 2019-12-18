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
struct mb86a16_state {int master_clk; } ;

/* Variables and functions */
 int EREMOTEIO ; 
 int /*<<< orphan*/  MB86A16_ERROR ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 
 int mb86a16_read (struct mb86a16_state*,int,unsigned char*) ; 
 int /*<<< orphan*/  verbose ; 

__attribute__((used)) static int afcerr_chk(struct mb86a16_state *state)
{
	unsigned char AFCM_L, AFCM_H ;
	int AFCM ;
	int afcm, afcerr ;

	if (mb86a16_read(state, 0x0e, &AFCM_L) != 2)
		goto err;
	if (mb86a16_read(state, 0x0f, &AFCM_H) != 2)
		goto err;

	AFCM = (AFCM_H << 8) + AFCM_L;

	if (AFCM > 2048)
		afcm = AFCM - 4096;
	else
		afcm = AFCM;
	afcerr = afcm * state->master_clk / 8192;

	return afcerr;

err:
	dprintk(verbose, MB86A16_ERROR, 1, "I2C transfer error");
	return -EREMOTEIO;
}