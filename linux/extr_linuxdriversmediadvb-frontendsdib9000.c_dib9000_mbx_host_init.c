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
typedef  int u8 ;
typedef  int u16 ;
struct dib9000_state {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int dib9000_read_word (struct dib9000_state*,int) ; 
 int /*<<< orphan*/  dib9000_write_word (struct dib9000_state*,int,int) ; 
 int /*<<< orphan*/  dprintk (char*,...) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static int dib9000_mbx_host_init(struct dib9000_state *state, u8 risc_id)
{
	u16 mbox_offs;
	u16 reset_reg;
	u16 tries = 1000;

	if (risc_id == 1)
		mbox_offs = 16;
	else
		mbox_offs = 0;

	/* Reset mailbox  */
	dib9000_write_word(state, 1027 + mbox_offs, 0x8000);

	/* Read reset status */
	do {
		reset_reg = dib9000_read_word(state, 1027 + mbox_offs);
		msleep(100);
	} while ((reset_reg & 0x8000) && --tries);

	if (reset_reg & 0x8000) {
		dprintk("MBX: init ERROR, no response from RISC %c\n", 'A' + risc_id);
		return -EIO;
	}
	dprintk("MBX: initialized\n");
	return 0;
}