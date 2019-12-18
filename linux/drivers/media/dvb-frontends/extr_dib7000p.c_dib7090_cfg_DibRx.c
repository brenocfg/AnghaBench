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
struct dib7000p_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dib7000p_write_word (struct dib7000p_state*,int,int) ; 
 int dib7090_calcSyncFreq (int,int,int,int) ; 
 int /*<<< orphan*/  dprintk (char*) ; 

__attribute__((used)) static int dib7090_cfg_DibRx(struct dib7000p_state *state, u32 P_Kin, u32 P_Kout, u32 synchroMode, u32 insertExtSynchro, u32 syncWord, u32 syncSize,
		u32 dataOutRate)
{
	u32 syncFreq;

	dprintk("Configure DibStream Rx\n");
	if ((P_Kin != 0) && (P_Kout != 0)) {
		syncFreq = dib7090_calcSyncFreq(P_Kin, P_Kout, insertExtSynchro, syncSize);
		dib7000p_write_word(state, 1542, syncFreq);
	}
	dib7000p_write_word(state, 1554, 1);
	dib7000p_write_word(state, 1536, P_Kin);
	dib7000p_write_word(state, 1537, P_Kout);
	dib7000p_write_word(state, 1539, synchroMode);
	dib7000p_write_word(state, 1540, (syncWord >> 16) & 0xffff);
	dib7000p_write_word(state, 1541, syncWord & 0xffff);
	dib7000p_write_word(state, 1543, syncSize);
	dib7000p_write_word(state, 1544, dataOutRate);
	dib7000p_write_word(state, 1554, 0);

	return 0;
}