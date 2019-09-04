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
struct sram_channel {unsigned int cmds_start; int ctrl_start; unsigned int ptr1_reg; unsigned int ptr2_reg; unsigned int cnt1_reg; unsigned int cnt2_reg; int /*<<< orphan*/  fifo_size; int /*<<< orphan*/  fifo_start; int /*<<< orphan*/  name; } ;
struct cx25821_dev {int /*<<< orphan*/ * i2c_bus; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  AFE_AB_DIAG_CTRL ; 
 unsigned int ARRAY_SIZE (char const* const*) ; 
 unsigned int AUD_A_CDT ; 
 unsigned int CLK_RST ; 
 int /*<<< orphan*/  CX25821_INFO (char*,unsigned int) ; 
 unsigned int PLL_A_INT_FRAC ; 
 unsigned int PLL_A_POST_STAT_BIST ; 
 unsigned int PLL_B_INT_FRAC ; 
 unsigned int PLL_B_POST_STAT_BIST ; 
 unsigned int PLL_C_INT_FRAC ; 
 unsigned int PLL_C_POST_STAT_BIST ; 
 unsigned int PLL_D_INT_FRAC ; 
 unsigned int PLL_D_POST_STAT_BIST ; 
 unsigned int cx25821_i2c_read (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int*) ; 
 unsigned int cx25821_risc_decode (unsigned int) ; 
 unsigned int cx_read (unsigned int) ; 
 int /*<<< orphan*/  pr_cont (char*,...) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,unsigned int,...) ; 
 int /*<<< orphan*/  pr_warn (char*,unsigned int,...) ; 

void cx25821_sram_channel_dump_audio(struct cx25821_dev *dev,
				     const struct sram_channel *ch)
{
	static const char * const name[] = {
		"init risc lo",
		"init risc hi",
		"cdt base",
		"cdt size",
		"iq base",
		"iq size",
		"risc pc lo",
		"risc pc hi",
		"iq wr ptr",
		"iq rd ptr",
		"cdt current",
		"pci target lo",
		"pci target hi",
		"line / byte",
	};

	u32 risc, value, tmp;
	unsigned int i, j, n;

	pr_info("\n%s: %s - dma Audio channel status dump\n",
		dev->name, ch->name);

	for (i = 0; i < ARRAY_SIZE(name); i++)
		pr_info("%s: cmds + 0x%2x:   %-15s: 0x%08x\n",
			dev->name, i * 4, name[i],
			cx_read(ch->cmds_start + 4 * i));

	j = i * 4;
	for (i = 0; i < 4;) {
		risc = cx_read(ch->cmds_start + 4 * (i + 14));
		pr_warn("cmds + 0x%2x:   risc%d: ", j + i * 4, i);
		i += cx25821_risc_decode(risc);
	}

	for (i = 0; i < (64 >> 2); i += n) {
		risc = cx_read(ch->ctrl_start + 4 * i);
		/* No consideration for bits 63-32 */

		pr_warn("ctrl + 0x%2x (0x%08x): iq %x: ",
			i * 4, ch->ctrl_start + 4 * i, i);
		n = cx25821_risc_decode(risc);

		for (j = 1; j < n; j++) {
			risc = cx_read(ch->ctrl_start + 4 * (i + j));
			pr_warn("ctrl + 0x%2x :   iq %x: 0x%08x [ arg #%d ]\n",
				4 * (i + j), i + j, risc, j);
		}
	}

	pr_warn("        :   fifo: 0x%08x -> 0x%x\n",
		ch->fifo_start, ch->fifo_start + ch->fifo_size);
	pr_warn("        :   ctrl: 0x%08x -> 0x%x\n",
		ch->ctrl_start, ch->ctrl_start + 6 * 16);
	pr_warn("        :   ptr1_reg: 0x%08x\n",
		cx_read(ch->ptr1_reg));
	pr_warn("        :   ptr2_reg: 0x%08x\n",
		cx_read(ch->ptr2_reg));
	pr_warn("        :   cnt1_reg: 0x%08x\n",
		cx_read(ch->cnt1_reg));
	pr_warn("        :   cnt2_reg: 0x%08x\n",
		cx_read(ch->cnt2_reg));

	for (i = 0; i < 4; i++) {
		risc = cx_read(ch->cmds_start + 56 + (i * 4));
		pr_warn("instruction %d = 0x%x\n", i, risc);
	}

	/* read data from the first cdt buffer */
	risc = cx_read(AUD_A_CDT);
	pr_warn("\nread cdt loc=0x%x\n", risc);
	for (i = 0; i < 8; i++) {
		n = cx_read(risc + i * 4);
		pr_cont("0x%x ", n);
	}
	pr_cont("\n\n");

	value = cx_read(CLK_RST);
	CX25821_INFO(" CLK_RST = 0x%x\n\n", value);

	value = cx_read(PLL_A_POST_STAT_BIST);
	CX25821_INFO(" PLL_A_POST_STAT_BIST = 0x%x\n\n", value);
	value = cx_read(PLL_A_INT_FRAC);
	CX25821_INFO(" PLL_A_INT_FRAC = 0x%x\n\n", value);

	value = cx_read(PLL_B_POST_STAT_BIST);
	CX25821_INFO(" PLL_B_POST_STAT_BIST = 0x%x\n\n", value);
	value = cx_read(PLL_B_INT_FRAC);
	CX25821_INFO(" PLL_B_INT_FRAC = 0x%x\n\n", value);

	value = cx_read(PLL_C_POST_STAT_BIST);
	CX25821_INFO(" PLL_C_POST_STAT_BIST = 0x%x\n\n", value);
	value = cx_read(PLL_C_INT_FRAC);
	CX25821_INFO(" PLL_C_INT_FRAC = 0x%x\n\n", value);

	value = cx_read(PLL_D_POST_STAT_BIST);
	CX25821_INFO(" PLL_D_POST_STAT_BIST = 0x%x\n\n", value);
	value = cx_read(PLL_D_INT_FRAC);
	CX25821_INFO(" PLL_D_INT_FRAC = 0x%x\n\n", value);

	value = cx25821_i2c_read(&dev->i2c_bus[0], AFE_AB_DIAG_CTRL, &tmp);
	CX25821_INFO(" AFE_AB_DIAG_CTRL (0x10900090) = 0x%x\n\n", value);
}