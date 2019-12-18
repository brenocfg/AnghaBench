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
typedef  int u16 ;
struct dib8000_state {int dummy; } ;

/* Variables and functions */
 int dib8000_read_word (struct dib8000_state*,int) ; 
 int /*<<< orphan*/  dib8000_write_word (struct dib8000_state*,int,int) ; 

__attribute__((used)) static void dib8000_set_subchannel_prbs(struct dib8000_state *state, u16 init_prbs)
{
	u16 reg_1;

	reg_1 = dib8000_read_word(state, 1);
	dib8000_write_word(state, 1, (init_prbs << 2) | (reg_1 & 0x3)); /* ADDR 1 */
}