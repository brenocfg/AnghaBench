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
typedef  int /*<<< orphan*/  u16 ;
struct dib7000m_state {int timf; int current_bandwidth; int /*<<< orphan*/  timf_default; } ;

/* Variables and functions */
 int dib7000m_read_word (struct dib7000m_state*,int) ; 
 int /*<<< orphan*/  dib7000m_write_word (struct dib7000m_state*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintk (char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dib7000m_update_timf(struct dib7000m_state *state)
{
	u32 timf = (dib7000m_read_word(state, 436) << 16) | dib7000m_read_word(state, 437);
	state->timf = timf * 160 / (state->current_bandwidth / 50);
	dib7000m_write_word(state, 23, (u16) (timf >> 16));
	dib7000m_write_word(state, 24, (u16) (timf & 0xffff));
	dprintk("updated timf_frequency: %d (default: %d)\n", state->timf, state->timf_default);
}