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
typedef  int /*<<< orphan*/  u32 ;
struct seq_file {int dummy; } ;
struct flexrm_ring {scalar_t__ cmpl_dma_base; scalar_t__ bd_dma_base; int /*<<< orphan*/  num; scalar_t__ regs; } ;
struct flexrm_mbox {int num_rings; struct flexrm_ring* rings; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CONTROL_ACTIVE_SHIFT ; 
 scalar_t__ RING_BD_SIZE ; 
 scalar_t__ RING_CMPL_SIZE ; 
 scalar_t__ RING_CONTROL ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,char*,char const*,...) ; 

__attribute__((used)) static void flexrm_write_config_in_seqfile(struct flexrm_mbox *mbox,
					   struct seq_file *file)
{
	int i;
	const char *state;
	struct flexrm_ring *ring;

	seq_printf(file, "%-5s %-9s %-18s %-10s %-18s %-10s\n",
		   "Ring#", "State", "BD_Addr", "BD_Size",
		   "Cmpl_Addr", "Cmpl_Size");

	for (i = 0; i < mbox->num_rings; i++) {
		ring = &mbox->rings[i];
		if (readl(ring->regs + RING_CONTROL) &
		    BIT(CONTROL_ACTIVE_SHIFT))
			state = "active";
		else
			state = "inactive";
		seq_printf(file,
			   "%-5d %-9s 0x%016llx 0x%08x 0x%016llx 0x%08x\n",
			   ring->num, state,
			   (unsigned long long)ring->bd_dma_base,
			   (u32)RING_BD_SIZE,
			   (unsigned long long)ring->cmpl_dma_base,
			   (u32)RING_CMPL_SIZE);
	}
}