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
 int /*<<< orphan*/  smrt_info_get (struct mb86a16_state*,int) ; 
 int /*<<< orphan*/  verbose ; 

__attribute__((used)) static int freqerr_chk(struct mb86a16_state *state,
		       int fTP,
		       int smrt,
		       int unit)
{
	unsigned char CRM, AFCML, AFCMH;
	unsigned char temp1, temp2, temp3;
	int crm, afcm, AFCM;
	int crrerr, afcerr;		/* kHz */
	int frqerr;			/* MHz */
	int afcen, afcexen = 0;
	int R, M, fOSC, fOSC_OFS;

	if (mb86a16_read(state, 0x43, &CRM) != 2)
		goto err;

	if (CRM > 127)
		crm = CRM - 256;
	else
		crm = CRM;

	crrerr = smrt * crm / 256;
	if (mb86a16_read(state, 0x49, &temp1) != 2)
		goto err;

	afcen = (temp1 & 0x04) >> 2;
	if (afcen == 0) {
		if (mb86a16_read(state, 0x2a, &temp1) != 2)
			goto err;
		afcexen = (temp1 & 0x20) >> 5;
	}

	if (afcen == 1) {
		if (mb86a16_read(state, 0x0e, &AFCML) != 2)
			goto err;
		if (mb86a16_read(state, 0x0f, &AFCMH) != 2)
			goto err;
	} else if (afcexen == 1) {
		if (mb86a16_read(state, 0x2b, &AFCML) != 2)
			goto err;
		if (mb86a16_read(state, 0x2c, &AFCMH) != 2)
			goto err;
	}
	if ((afcen == 1) || (afcexen == 1)) {
		smrt_info_get(state, smrt);
		AFCM = ((AFCMH & 0x01) << 8) + AFCML;
		if (AFCM > 255)
			afcm = AFCM - 512;
		else
			afcm = AFCM;

		afcerr = afcm * state->master_clk / 8192;
	} else
		afcerr = 0;

	if (mb86a16_read(state, 0x22, &temp1) != 2)
		goto err;
	if (mb86a16_read(state, 0x23, &temp2) != 2)
		goto err;
	if (mb86a16_read(state, 0x24, &temp3) != 2)
		goto err;

	R = (temp1 & 0xe0) >> 5;
	M = ((temp1 & 0x1f) << 12) + (temp2 << 4) + (temp3 >> 4);
	if (R == 0)
		fOSC = 2 * M;
	else
		fOSC = M;

	fOSC_OFS = fOSC - fTP;

	if (unit == 0) {	/* MHz */
		if (crrerr + afcerr + fOSC_OFS * 1000 >= 0)
			frqerr = (crrerr + afcerr + fOSC_OFS * 1000 + 500) / 1000;
		else
			frqerr = (crrerr + afcerr + fOSC_OFS * 1000 - 500) / 1000;
	} else {	/* kHz */
		frqerr = crrerr + afcerr + fOSC_OFS * 1000;
	}

	return frqerr;
err:
	dprintk(verbose, MB86A16_ERROR, 1, "I2C transfer error");
	return -EREMOTEIO;
}