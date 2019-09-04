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
typedef  int u32 ;
struct stv0367_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  R367CAB_SRC_NCO_HH ; 
 int /*<<< orphan*/  R367CAB_SRC_NCO_HL ; 
 int /*<<< orphan*/  R367CAB_SRC_NCO_LH ; 
 int /*<<< orphan*/  R367CAB_SRC_NCO_LL ; 
 int stv0367_readreg (struct stv0367_state*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 stv0367cab_GetSymbolRate(struct stv0367_state *state, u32 mclk_hz)
{
	u32 regsym;
	u32 adp_khz;

	regsym = stv0367_readreg(state, R367CAB_SRC_NCO_LL) +
		(stv0367_readreg(state, R367CAB_SRC_NCO_LH) << 8) +
		(stv0367_readreg(state, R367CAB_SRC_NCO_HL) << 16) +
		(stv0367_readreg(state, R367CAB_SRC_NCO_HH) << 24);

	adp_khz = (mclk_hz >> 1) / 1000;/* TRL works at half the system clock */

	if (regsym < 134217728) {		/* 134217728L = 2**27*/
		regsym = regsym * 32;		/* 32 = 2**5 */
		regsym = regsym / 32768;	/* 32768L = 2**15 */
		regsym = adp_khz * regsym;	/* AdpClk in kHz */
		regsym = regsym / 128;		/* 128 = 2**7 */
		regsym *= 125 ;			/* 125 = 1000/2**3 */
		regsym /= 2048 ;		/* 2048 = 2**11	*/
	} else if (regsym < 268435456) {	/* 268435456L = 2**28 */
		regsym = regsym * 16;		/* 16 = 2**4 */
		regsym = regsym / 32768;	/* 32768L = 2**15 */
		regsym = adp_khz * regsym;	/* AdpClk in kHz */
		regsym = regsym / 128;		/* 128 = 2**7 */
		regsym *= 125 ;			/* 125 = 1000/2**3*/
		regsym /= 1024 ;		/* 256 = 2**10*/
	} else if (regsym < 536870912) {	/* 536870912L = 2**29*/
		regsym = regsym * 8;		/* 8 = 2**3 */
		regsym = regsym / 32768;	/* 32768L = 2**15 */
		regsym = adp_khz * regsym;	/* AdpClk in kHz */
		regsym = regsym / 128;		/* 128 = 2**7 */
		regsym *= 125 ;			/* 125 = 1000/2**3 */
		regsym /= 512 ;			/* 128 = 2**9 */
	} else {
		regsym = regsym * 4;		/* 4 = 2**2 */
		regsym = regsym / 32768;	/* 32768L = 2**15 */
		regsym = adp_khz * regsym;	/* AdpClk in kHz */
		regsym = regsym / 128;		/* 128 = 2**7 */
		regsym *= 125 ;			/* 125 = 1000/2**3 */
		regsym /= 256 ;			/* 64 = 2**8 */
	}

	return regsym;
}