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
struct ntb_dev {int dummy; } ;
struct idt_ntb_dev {int peer_cnt; int mw_cnt; int /*<<< orphan*/  lut_lock; struct idt_mw_cfg* mws; } ;
struct idt_ntb_bar {int /*<<< orphan*/  limit; int /*<<< orphan*/  setup; } ;
struct idt_mw_cfg {scalar_t__ type; size_t bar; size_t idx; } ;
struct TYPE_2__ {struct idt_ntb_bar* bars; } ;

/* Variables and functions */
 int /*<<< orphan*/  BARSETUP_TYPE ; 
 int EINVAL ; 
 scalar_t__ IDT_MW_DIR ; 
 int /*<<< orphan*/  IDT_NT_LUTLDATA ; 
 int /*<<< orphan*/  IDT_NT_LUTMDATA ; 
 int /*<<< orphan*/  IDT_NT_LUTOFFSET ; 
 int /*<<< orphan*/  IDT_NT_LUTUDATA ; 
 scalar_t__ IS_FLD_SET (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  LUTOFFSET_BAR ; 
 int /*<<< orphan*/  LUTOFFSET_INDEX ; 
 int SET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int idt_nt_read (struct idt_ntb_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idt_nt_write (struct idt_ntb_dev*,int /*<<< orphan*/ ,int) ; 
 TYPE_1__ ntdata_tbl ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct idt_ntb_dev* to_ndev_ntb (struct ntb_dev*) ; 

__attribute__((used)) static int idt_ntb_peer_mw_clear_trans(struct ntb_dev *ntb, int pidx,
					int widx)
{
	struct idt_ntb_dev *ndev = to_ndev_ntb(ntb);
	struct idt_mw_cfg *mw_cfg;

	if (pidx < 0 || ndev->peer_cnt <= pidx)
		return -EINVAL;

	if (widx < 0 || ndev->mw_cnt <= widx)
		return -EINVAL;

	mw_cfg = &ndev->mws[widx];

	/* DIR and LUT based translations are initialized differently */
	if (mw_cfg->type == IDT_MW_DIR) {
		const struct idt_ntb_bar *bar = &ntdata_tbl.bars[mw_cfg->bar];
		u32 data;
		/* Read BARSETUP to check BAR type */
		data = idt_nt_read(ndev, bar->setup);
		/* Disable translation by specifying zero BAR limit */
		idt_nt_write(ndev, bar->limit, 0);
		if (IS_FLD_SET(BARSETUP_TYPE, data, 64))
			idt_nt_write(ndev, (bar + 1)->limit, 0);
	} else {
		unsigned long irqflags;
		u32 lutoff;
		/* Clear the corresponding LUT entry up */
		lutoff = SET_FIELD(LUTOFFSET_INDEX, 0, mw_cfg->idx) |
			 SET_FIELD(LUTOFFSET_BAR, 0, mw_cfg->bar);
		spin_lock_irqsave(&ndev->lut_lock, irqflags);
		idt_nt_write(ndev, IDT_NT_LUTOFFSET, lutoff);
		idt_nt_write(ndev, IDT_NT_LUTLDATA, 0);
		idt_nt_write(ndev, IDT_NT_LUTMDATA, 0);
		idt_nt_write(ndev, IDT_NT_LUTUDATA, 0);
		spin_unlock_irqrestore(&ndev->lut_lock, irqflags);
	}

	return 0;
}