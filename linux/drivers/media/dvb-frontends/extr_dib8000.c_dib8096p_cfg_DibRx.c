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
struct dib8000_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dib8000_write_word (struct dib8000_state*,int,int) ; 
 int dib8096p_calcSyncFreq (int,int,int,int) ; 
 int /*<<< orphan*/  dprintk (char*,int) ; 

__attribute__((used)) static void dib8096p_cfg_DibRx(struct dib8000_state *state, u32 P_Kin,
		u32 P_Kout, u32 synchroMode, u32 insertExtSynchro,
		u32 syncWord, u32 syncSize, u32 dataOutRate)
{
	u32 syncFreq;

	dprintk("Configure DibStream Rx synchroMode = %d\n", synchroMode);

	if ((P_Kin != 0) && (P_Kout != 0)) {
		syncFreq = dib8096p_calcSyncFreq(P_Kin, P_Kout,
				insertExtSynchro, syncSize);
		dib8000_write_word(state, 1542, syncFreq);
	}

	dib8000_write_word(state, 1554, 1);
	dib8000_write_word(state, 1536, P_Kin);
	dib8000_write_word(state, 1537, P_Kout);
	dib8000_write_word(state, 1539, synchroMode);
	dib8000_write_word(state, 1540, (syncWord >> 16) & 0xffff);
	dib8000_write_word(state, 1541, syncWord & 0xffff);
	dib8000_write_word(state, 1543, syncSize);
	dib8000_write_word(state, 1544, dataOutRate);
	dib8000_write_word(state, 1554, 0);
}