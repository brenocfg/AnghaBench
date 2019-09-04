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
struct seq_file {struct mic_device* private; } ;
struct TYPE_3__ {int num_reg; } ;
struct mic_smpt_info {int /*<<< orphan*/  smpt_lock; TYPE_2__* entry; TYPE_1__ info; } ;
struct mic_device {struct mic_smpt_info* smpt; int /*<<< orphan*/  id; } ;
struct TYPE_4__ {int /*<<< orphan*/  ref_count; int /*<<< orphan*/  dma_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,char*,...) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int mic_smpt_show(struct seq_file *s, void *pos)
{
	int i;
	struct mic_device *mdev = s->private;
	unsigned long flags;

	seq_printf(s, "MIC %-2d |%-10s| %-14s %-10s\n",
		   mdev->id, "SMPT entry", "SW DMA addr", "RefCount");
	seq_puts(s, "====================================================\n");

	if (mdev->smpt) {
		struct mic_smpt_info *smpt_info = mdev->smpt;
		spin_lock_irqsave(&smpt_info->smpt_lock, flags);
		for (i = 0; i < smpt_info->info.num_reg; i++) {
			seq_printf(s, "%9s|%-10d| %-#14llx %-10lld\n",
				   " ",  i, smpt_info->entry[i].dma_addr,
				   smpt_info->entry[i].ref_count);
		}
		spin_unlock_irqrestore(&smpt_info->smpt_lock, flags);
	}
	seq_puts(s, "====================================================\n");
	return 0;
}