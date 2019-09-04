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
struct rtsx_slot {int dummy; } ;
struct rtsx_pcr {int /*<<< orphan*/  slots; int /*<<< orphan*/  state; int /*<<< orphan*/  flags; int /*<<< orphan*/  card_drive_sel; int /*<<< orphan*/  sd30_drive_sel_3v3; int /*<<< orphan*/  sd30_drive_sel_1v8; int /*<<< orphan*/  aspm_en; TYPE_1__* ops; int /*<<< orphan*/  num_slots; int /*<<< orphan*/  ic_version; int /*<<< orphan*/  pcr_mutex; int /*<<< orphan*/  lock; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* fetch_vendor_settings ) (struct rtsx_pcr*) ;} ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PCI_PID (struct rtsx_pcr*) ; 
 int /*<<< orphan*/  PDEV_STAT_IDLE ; 
 int /*<<< orphan*/  kcalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pcr_dbg (struct rtsx_pcr*,char*,int,...) ; 
 int /*<<< orphan*/  rtl8402_init_params (struct rtsx_pcr*) ; 
 int /*<<< orphan*/  rtl8411_init_params (struct rtsx_pcr*) ; 
 int /*<<< orphan*/  rtl8411b_init_params (struct rtsx_pcr*) ; 
 int /*<<< orphan*/  rts5209_init_params (struct rtsx_pcr*) ; 
 int /*<<< orphan*/  rts5227_init_params (struct rtsx_pcr*) ; 
 int /*<<< orphan*/  rts5229_init_params (struct rtsx_pcr*) ; 
 int /*<<< orphan*/  rts522a_init_params (struct rtsx_pcr*) ; 
 int /*<<< orphan*/  rts5249_init_params (struct rtsx_pcr*) ; 
 int /*<<< orphan*/  rts524a_init_params (struct rtsx_pcr*) ; 
 int /*<<< orphan*/  rts525a_init_params (struct rtsx_pcr*) ; 
 int /*<<< orphan*/  rts5260_init_params (struct rtsx_pcr*) ; 
 int rtsx_pci_init_hw (struct rtsx_pcr*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct rtsx_pcr*) ; 

__attribute__((used)) static int rtsx_pci_init_chip(struct rtsx_pcr *pcr)
{
	int err;

	spin_lock_init(&pcr->lock);
	mutex_init(&pcr->pcr_mutex);

	switch (PCI_PID(pcr)) {
	default:
	case 0x5209:
		rts5209_init_params(pcr);
		break;

	case 0x5229:
		rts5229_init_params(pcr);
		break;

	case 0x5289:
		rtl8411_init_params(pcr);
		break;

	case 0x5227:
		rts5227_init_params(pcr);
		break;

	case 0x522A:
		rts522a_init_params(pcr);
		break;

	case 0x5249:
		rts5249_init_params(pcr);
		break;

	case 0x524A:
		rts524a_init_params(pcr);
		break;

	case 0x525A:
		rts525a_init_params(pcr);
		break;

	case 0x5287:
		rtl8411b_init_params(pcr);
		break;

	case 0x5286:
		rtl8402_init_params(pcr);
		break;
	case 0x5260:
		rts5260_init_params(pcr);
		break;
	}

	pcr_dbg(pcr, "PID: 0x%04x, IC version: 0x%02x\n",
			PCI_PID(pcr), pcr->ic_version);

	pcr->slots = kcalloc(pcr->num_slots, sizeof(struct rtsx_slot),
			GFP_KERNEL);
	if (!pcr->slots)
		return -ENOMEM;

	if (pcr->ops->fetch_vendor_settings)
		pcr->ops->fetch_vendor_settings(pcr);

	pcr_dbg(pcr, "pcr->aspm_en = 0x%x\n", pcr->aspm_en);
	pcr_dbg(pcr, "pcr->sd30_drive_sel_1v8 = 0x%x\n",
			pcr->sd30_drive_sel_1v8);
	pcr_dbg(pcr, "pcr->sd30_drive_sel_3v3 = 0x%x\n",
			pcr->sd30_drive_sel_3v3);
	pcr_dbg(pcr, "pcr->card_drive_sel = 0x%x\n",
			pcr->card_drive_sel);
	pcr_dbg(pcr, "pcr->flags = 0x%x\n", pcr->flags);

	pcr->state = PDEV_STAT_IDLE;
	err = rtsx_pci_init_hw(pcr);
	if (err < 0) {
		kfree(pcr->slots);
		return err;
	}

	return 0;
}