#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  rx_pool; } ;
struct vc_map {int index; TYPE_1__ rcv; } ;
struct idt77252_dev {int vpibits; int rct_base; int /*<<< orphan*/  cmd_lock; struct vc_map** vcs; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned long SAR_CMD_OPEN_CONNECTION ; 
 int SAR_RCTE_CONNECTOPEN ; 
 int SAR_RCTE_FBP_1 ; 
 int SAR_RCTE_RAWCELLINTEN ; 
 int SAR_RCTE_RCQ ; 
 int /*<<< orphan*/  SAR_REG_CMD ; 
 int VPCI2VC (struct idt77252_dev*,int,int) ; 
 int /*<<< orphan*/  flush_rx_pool (struct idt77252_dev*,int /*<<< orphan*/ *) ; 
 struct vc_map* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  waitfor_idle (struct idt77252_dev*) ; 
 int /*<<< orphan*/  write_sram (struct idt77252_dev*,unsigned long,int) ; 
 int /*<<< orphan*/  writel (unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
open_card_oam(struct idt77252_dev *card)
{
	unsigned long flags;
	unsigned long addr;
	struct vc_map *vc;
	int vpi, vci;
	int index;
	u32 rcte;

	for (vpi = 0; vpi < (1 << card->vpibits); vpi++) {
		for (vci = 3; vci < 5; vci++) {
			index = VPCI2VC(card, vpi, vci);

			vc = kzalloc(sizeof(struct vc_map), GFP_KERNEL);
			if (!vc) {
				printk("%s: can't alloc vc\n", card->name);
				return -ENOMEM;
			}
			vc->index = index;
			card->vcs[index] = vc;

			flush_rx_pool(card, &vc->rcv.rx_pool);

			rcte = SAR_RCTE_CONNECTOPEN |
			       SAR_RCTE_RAWCELLINTEN |
			       SAR_RCTE_RCQ |
			       SAR_RCTE_FBP_1;

			addr = card->rct_base + (vc->index << 2);
			write_sram(card, addr, rcte);

			spin_lock_irqsave(&card->cmd_lock, flags);
			writel(SAR_CMD_OPEN_CONNECTION | (addr << 2),
			       SAR_REG_CMD);
			waitfor_idle(card);
			spin_unlock_irqrestore(&card->cmd_lock, flags);
		}
	}

	return 0;
}