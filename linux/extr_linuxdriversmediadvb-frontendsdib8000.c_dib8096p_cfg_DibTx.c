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
 int /*<<< orphan*/  dprintk (char*) ; 

__attribute__((used)) static void dib8096p_cfg_DibTx(struct dib8000_state *state, u32 P_Kin,
		u32 P_Kout, u32 insertExtSynchro, u32 synchroMode,
		u32 syncWord, u32 syncSize)
{
	dprintk("Configure DibStream Tx\n");

	dib8000_write_word(state, 1615, 1);
	dib8000_write_word(state, 1603, P_Kin);
	dib8000_write_word(state, 1605, P_Kout);
	dib8000_write_word(state, 1606, insertExtSynchro);
	dib8000_write_word(state, 1608, synchroMode);
	dib8000_write_word(state, 1609, (syncWord >> 16) & 0xffff);
	dib8000_write_word(state, 1610, syncWord & 0xffff);
	dib8000_write_word(state, 1612, syncSize);
	dib8000_write_word(state, 1615, 0);
}