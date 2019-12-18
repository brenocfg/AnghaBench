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
typedef  int /*<<< orphan*/  u32 ;
struct stb0899_state {int /*<<< orphan*/  verbose; } ;
typedef  enum stb0899_status { ____Placeholder_stb0899_status } stb0899_status ;

/* Variables and functions */
 int /*<<< orphan*/  CSM_LOCK ; 
 int /*<<< orphan*/  DMD_STAT2 ; 
 int /*<<< orphan*/  DMD_STATUS ; 
 int DVBS2_DEMOD_LOCK ; 
 int DVBS2_DEMOD_NOLOCK ; 
 int /*<<< orphan*/  FE_DEBUG ; 
 int /*<<< orphan*/  IF_AGC_LOCK ; 
 int STB0899_GETFIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STB0899_READ_S2REG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STB0899_S2DEMOD ; 
 int /*<<< orphan*/  UWP_LOCK ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,...) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static enum stb0899_status stb0899_dvbs2_get_dmd_status(struct stb0899_state *state, int timeout)
{
	int time = -10, lock = 0, uwp, csm;
	u32 reg;

	do {
		reg = STB0899_READ_S2REG(STB0899_S2DEMOD, DMD_STATUS);
		dprintk(state->verbose, FE_DEBUG, 1, "DMD_STATUS=[0x%02x]", reg);
		if (STB0899_GETFIELD(IF_AGC_LOCK, reg))
			dprintk(state->verbose, FE_DEBUG, 1, "------------->IF AGC LOCKED !");
		reg = STB0899_READ_S2REG(STB0899_S2DEMOD, DMD_STAT2);
		dprintk(state->verbose, FE_DEBUG, 1, "----------->DMD STAT2=[0x%02x]", reg);
		uwp = STB0899_GETFIELD(UWP_LOCK, reg);
		csm = STB0899_GETFIELD(CSM_LOCK, reg);
		if (uwp && csm)
			lock = 1;

		time += 10;
		msleep(10);

	} while ((!lock) && (time <= timeout));

	if (lock) {
		dprintk(state->verbose, FE_DEBUG, 1, "----------------> DVB-S2 LOCK !");
		return DVBS2_DEMOD_LOCK;
	} else {
		return DVBS2_DEMOD_NOLOCK;
	}
}