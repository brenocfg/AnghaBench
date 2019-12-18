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
typedef  unsigned int u32 ;
struct sram_channel {unsigned int name; int fifo_size; scalar_t__ cnt2_reg; scalar_t__ cnt1_reg; scalar_t__ ptr2_reg; scalar_t__ ptr1_reg; scalar_t__ ctrl_start; int /*<<< orphan*/  fifo_start; scalar_t__ cmds_start; } ;
struct cx88_core {int dummy; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (char const* const*) ; 
 unsigned int cx88_risc_decode (unsigned int) ; 
 unsigned int cx_read (scalar_t__) ; 
 int /*<<< orphan*/  dprintk0 (char*,...) ; 
 int /*<<< orphan*/  pr_cont (char*,unsigned int,...) ; 

void cx88_sram_channel_dump(struct cx88_core *core,
			    const struct sram_channel *ch)
{
	static const char * const name[] = {
		"initial risc",
		"cdt base",
		"cdt size",
		"iq base",
		"iq size",
		"risc pc",
		"iq wr ptr",
		"iq rd ptr",
		"cdt current",
		"pci target",
		"line / byte",
	};
	u32 risc;
	unsigned int i, j, n;

	dprintk0("%s - dma channel status dump\n", ch->name);
	for (i = 0; i < ARRAY_SIZE(name); i++)
		dprintk0("   cmds: %-12s: 0x%08x\n",
			 name[i], cx_read(ch->cmds_start + 4 * i));
	for (n = 1, i = 0; i < 4; i++) {
		risc = cx_read(ch->cmds_start + 4 * (i + 11));
		pr_cont("  risc%d: ", i);
		if (--n)
			pr_cont("0x%08x [ arg #%d ]\n", risc, n);
		else
			n = cx88_risc_decode(risc);
	}
	for (i = 0; i < 16; i += n) {
		risc = cx_read(ch->ctrl_start + 4 * i);
		dprintk0("  iq %x: ", i);
		n = cx88_risc_decode(risc);
		for (j = 1; j < n; j++) {
			risc = cx_read(ch->ctrl_start + 4 * (i + j));
			pr_cont("  iq %x: 0x%08x [ arg #%d ]\n",
				i + j, risc, j);
		}
	}

	dprintk0("fifo: 0x%08x -> 0x%x\n",
		 ch->fifo_start, ch->fifo_start + ch->fifo_size);
	dprintk0("ctrl: 0x%08x -> 0x%x\n",
		 ch->ctrl_start, ch->ctrl_start + 6 * 16);
	dprintk0("  ptr1_reg: 0x%08x\n", cx_read(ch->ptr1_reg));
	dprintk0("  ptr2_reg: 0x%08x\n", cx_read(ch->ptr2_reg));
	dprintk0("  cnt1_reg: 0x%08x\n", cx_read(ch->cnt1_reg));
	dprintk0("  cnt2_reg: 0x%08x\n", cx_read(ch->cnt2_reg));
}