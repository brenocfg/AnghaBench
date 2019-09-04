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
typedef  int u64 ;
typedef  int u32 ;
struct seq_file {int dummy; } ;
struct mvebu_mbus_state {scalar_t__ sdramwins_base; } ;

/* Variables and functions */
 scalar_t__ DOVE_DDR_BASE_CS_OFF (int) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int,...) ; 

__attribute__((used)) static int mvebu_sdram_debug_show_dove(struct mvebu_mbus_state *mbus,
				       struct seq_file *seq, void *v)
{
	int i;

	for (i = 0; i < 2; i++) {
		u32 map = readl(mbus->sdramwins_base + DOVE_DDR_BASE_CS_OFF(i));
		u64 base;
		u32 size;

		if (!(map & 1)) {
			seq_printf(seq, "[%d] disabled\n", i);
			continue;
		}

		base = map & 0xff800000;
		size = 0x100000 << (((map & 0x000f0000) >> 16) - 4);

		seq_printf(seq, "[%d] %016llx - %016llx : cs%d\n",
			   i, (unsigned long long)base,
			   (unsigned long long)base + size, i);
	}

	return 0;
}