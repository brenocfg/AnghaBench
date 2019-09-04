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
typedef  int u16 ;
struct dib8000_state {int revision; } ;

/* Variables and functions */
 int /*<<< orphan*/  dib8000_write_word (struct dib8000_state*,int,int) ; 

__attribute__((used)) static u32 dib8000_wait_lock(struct dib8000_state *state, u32 internal,
			     u32 wait0_ms, u32 wait1_ms, u32 wait2_ms)
{
	u32 value = 0;	/* P_search_end0 wait time */
	u16 reg = 11;	/* P_search_end0 start addr */

	for (reg = 11; reg < 16; reg += 2) {
		if (reg == 11) {
			if (state->revision == 0x8090)
				value = internal * wait1_ms;
			else
				value = internal * wait0_ms;
		} else if (reg == 13)
			value = internal * wait1_ms;
		else if (reg == 15)
			value = internal * wait2_ms;
		dib8000_write_word(state, reg, (u16)((value >> 16) & 0xffff));
		dib8000_write_word(state, (reg + 1), (u16)(value & 0xffff));
	}
	return value;
}