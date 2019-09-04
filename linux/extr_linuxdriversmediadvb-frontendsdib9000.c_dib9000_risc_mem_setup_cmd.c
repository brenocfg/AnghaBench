#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct TYPE_3__ {int memcmd; } ;
struct TYPE_4__ {TYPE_1__ risc; } ;
struct dib9000_state {TYPE_2__ platform; } ;

/* Variables and functions */
 int /*<<< orphan*/  dib9000_write (struct dib9000_state*,int,int*,int) ; 
 int /*<<< orphan*/  dib9000_write_word (struct dib9000_state*,int,int) ; 

__attribute__((used)) static void dib9000_risc_mem_setup_cmd(struct dib9000_state *state, u32 addr, u32 len, u8 reading)
{
	u8 b[14] = { 0 };

/*      dprintk("%d memcmd: %d %d %d\n", state->fe_id, addr, addr+len, len); */
/*      b[0] = 0 << 7; */
	b[1] = 1;

/*      b[2] = 0; */
/*      b[3] = 0; */
	b[4] = (u8) (addr >> 8);
	b[5] = (u8) (addr & 0xff);

/*      b[10] = 0; */
/*      b[11] = 0; */
	b[12] = (u8) (addr >> 8);
	b[13] = (u8) (addr & 0xff);

	addr += len;
/*      b[6] = 0; */
/*      b[7] = 0; */
	b[8] = (u8) (addr >> 8);
	b[9] = (u8) (addr & 0xff);

	dib9000_write(state, 1056, b, 14);
	if (reading)
		dib9000_write_word(state, 1056, (1 << 15) | 1);
	state->platform.risc.memcmd = -1;	/* if it was called directly reset it - to force a future setup-call to set it */
}