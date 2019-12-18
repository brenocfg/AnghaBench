#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct seq_file {struct brcms_pub* private; } ;
struct brcms_pub {TYPE_4__* wlc; } ;
struct brcms_hardware {int /*<<< orphan*/  sromrev; TYPE_6__* band; int /*<<< orphan*/  boardflags2; int /*<<< orphan*/  boardflags; int /*<<< orphan*/  boardrev; struct bcma_device* d11core; } ;
struct TYPE_8__ {int /*<<< orphan*/  rev; } ;
struct bcma_device {TYPE_2__ id; struct bcma_bus* bus; } ;
struct TYPE_9__ {int /*<<< orphan*/  vendor; int /*<<< orphan*/  type; } ;
struct TYPE_7__ {int /*<<< orphan*/  pkg; int /*<<< orphan*/  rev; int /*<<< orphan*/  id; } ;
struct bcma_bus {TYPE_3__ boardinfo; TYPE_1__ chipinfo; } ;
struct TYPE_12__ {TYPE_5__* pi; int /*<<< orphan*/  phyrev; int /*<<< orphan*/  phytype; int /*<<< orphan*/  radiorev; } ;
struct TYPE_11__ {int /*<<< orphan*/  ana_rev; } ;
struct TYPE_10__ {int /*<<< orphan*/  ucode_rev; struct brcms_hardware* hw; } ;

/* Variables and functions */
 int BRCMU_BOARDREV_LEN ; 
 int /*<<< orphan*/  brcmu_boardrev_str (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
int brcms_debugfs_hardware_read(struct seq_file *s, void *data)
{
	struct brcms_pub *drvr = s->private;
	struct brcms_hardware *hw = drvr->wlc->hw;
	struct bcma_device *core = hw->d11core;
	struct bcma_bus *bus = core->bus;
	char boardrev[BRCMU_BOARDREV_LEN];

	seq_printf(s, "chipnum 0x%x\n"
		   "chiprev 0x%x\n"
		   "chippackage 0x%x\n"
		   "corerev 0x%x\n"
		   "boardid 0x%x\n"
		   "boardvendor 0x%x\n"
		   "boardrev %s\n"
		   "boardflags 0x%x\n"
		   "boardflags2 0x%x\n"
		   "ucoderev 0x%x\n"
		   "radiorev 0x%x\n"
		   "phytype 0x%x\n"
		   "phyrev 0x%x\n"
		   "anarev 0x%x\n"
		   "nvramrev %d\n",
		   bus->chipinfo.id, bus->chipinfo.rev, bus->chipinfo.pkg,
		   core->id.rev, bus->boardinfo.type, bus->boardinfo.vendor,
		   brcmu_boardrev_str(hw->boardrev, boardrev),
		   drvr->wlc->hw->boardflags, drvr->wlc->hw->boardflags2,
		   drvr->wlc->ucode_rev, hw->band->radiorev,
		   hw->band->phytype, hw->band->phyrev, hw->band->pi->ana_rev,
		   hw->sromrev);
	return 0;
}