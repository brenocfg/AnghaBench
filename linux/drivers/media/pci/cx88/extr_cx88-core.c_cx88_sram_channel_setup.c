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
struct sram_channel {int cdt; unsigned int fifo_size; unsigned int fifo_start; int cmds_start; unsigned int ctrl_start; int ptr1_reg; int ptr2_reg; int cnt1_reg; int cnt2_reg; int /*<<< orphan*/  name; } ;
struct cx88_core {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  cx_write (int,unsigned int) ; 
 int /*<<< orphan*/  dprintk (int,char*,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 

int cx88_sram_channel_setup(struct cx88_core *core,
			    const struct sram_channel *ch,
			    unsigned int bpl, u32 risc)
{
	unsigned int i, lines;
	u32 cdt;

	bpl   = (bpl + 7) & ~7; /* alignment */
	cdt   = ch->cdt;
	lines = ch->fifo_size / bpl;
	if (lines > 6)
		lines = 6;
	WARN_ON(lines < 2);

	/* write CDT */
	for (i = 0; i < lines; i++)
		cx_write(cdt + 16 * i, ch->fifo_start + bpl * i);

	/* write CMDS */
	cx_write(ch->cmds_start +  0, risc);
	cx_write(ch->cmds_start +  4, cdt);
	cx_write(ch->cmds_start +  8, (lines * 16) >> 3);
	cx_write(ch->cmds_start + 12, ch->ctrl_start);
	cx_write(ch->cmds_start + 16, 64 >> 2);
	for (i = 20; i < 64; i += 4)
		cx_write(ch->cmds_start + i, 0);

	/* fill registers */
	cx_write(ch->ptr1_reg, ch->fifo_start);
	cx_write(ch->ptr2_reg, cdt);
	cx_write(ch->cnt1_reg, (bpl >> 3) - 1);
	cx_write(ch->cnt2_reg, (lines * 16) >> 3);

	dprintk(2, "sram setup %s: bpl=%d lines=%d\n", ch->name, bpl, lines);
	return 0;
}