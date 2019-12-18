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
 int /*<<< orphan*/  dprintk (char*) ; 

__attribute__((used)) static int dib8090p_init_sdram(struct dib8000_state *state)
{
	u16 reg = 0;
	dprintk("init sdram\n");

	reg = dib8000_read_word(state, 274) & 0xfff0;
	dib8000_write_word(state, 274, reg | 0x7); /* P_dintlv_delay_ram = 7 because of MobileSdram */

	dib8000_write_word(state, 1803, (7 << 2));

	reg = dib8000_read_word(state, 1280);
	dib8000_write_word(state, 1280,  reg | (1 << 2)); /* force restart P_restart_sdram */
	dib8000_write_word(state, 1280,  reg); /* release restart P_restart_sdram */

	return 0;
}