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
typedef  scalar_t__ u64 ;
typedef  int u32 ;
struct sn_flush_nasid_entry {scalar_t__* iio_itte; struct sn_flush_device_kernel** widget_p; } ;
struct sn_flush_device_kernel {int /*<<< orphan*/  sfdl_flush_lock; struct sn_flush_device_common* common; } ;
struct sn_flush_device_common {int* sfdl_flush_addr; scalar_t__ sfdl_force_int_addr; scalar_t__ sfdl_slot; int /*<<< orphan*/  sfdl_pcibus_info; TYPE_1__* sfdl_bar_list; } ;
struct hubdev_info {struct sn_flush_nasid_entry hdi_flush_nasid_list; } ;
typedef  int nasid_t ;
struct TYPE_4__ {struct hubdev_info* pdinfo; } ;
struct TYPE_3__ {scalar_t__ start; scalar_t__ end; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 size_t BWIN_WINDOWNUM (scalar_t__) ; 
 int DEV_PER_WIDGET ; 
 int HUB_L (int /*<<< orphan*/ ) ; 
 int IIO_ITTE_WIDGET (scalar_t__) ; 
 int NASID_GET (scalar_t__) ; 
 TYPE_2__* NODEPDA (int) ; 
 int PCI_ROM_RESOURCE ; 
 int PV907516 ; 
 int SWIN_WIDGETNUM (scalar_t__) ; 
 int TIO_BWIN_WINDOWNUM (scalar_t__) ; 
 scalar_t__ TIO_HWIN (scalar_t__) ; 
 int /*<<< orphan*/  TIO_IOSPACE_ADDR (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TIO_ITTE_VALID (scalar_t__) ; 
 int TIO_ITTE_WIDGET (scalar_t__) ; 
 int /*<<< orphan*/  TIO_NODE_ID ; 
 int TIO_SWIN_WIDGETNUM (scalar_t__) ; 
 int XWIDGET_PART_REV_NUM (int) ; 
 int XWIDGET_PART_REV_NUM_REV (int) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int nasid_to_cnodeid (int) ; 
 int /*<<< orphan*/  pcireg_wrb_flush_get (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  sn_ioif_inited ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void sn_dma_flush(u64 addr)
{
	nasid_t nasid;
	int is_tio;
	int wid_num;
	int i, j;
	unsigned long flags;
	u64 itte;
	struct hubdev_info *hubinfo;
	struct sn_flush_device_kernel *p;
	struct sn_flush_device_common *common;
	struct sn_flush_nasid_entry *flush_nasid_list;

	if (!sn_ioif_inited)
		return;

	nasid = NASID_GET(addr);
	if (-1 == nasid_to_cnodeid(nasid))
		return;

	hubinfo = (NODEPDA(nasid_to_cnodeid(nasid)))->pdinfo;

	BUG_ON(!hubinfo);

	flush_nasid_list = &hubinfo->hdi_flush_nasid_list;
	if (flush_nasid_list->widget_p == NULL)
		return;

	is_tio = (nasid & 1);
	if (is_tio) {
		int itte_index;

		if (TIO_HWIN(addr))
			itte_index = 0;
		else if (TIO_BWIN_WINDOWNUM(addr))
			itte_index = TIO_BWIN_WINDOWNUM(addr);
		else
			itte_index = -1;

		if (itte_index >= 0) {
			itte = flush_nasid_list->iio_itte[itte_index];
			if (! TIO_ITTE_VALID(itte))
				return;
			wid_num = TIO_ITTE_WIDGET(itte);
		} else
			wid_num = TIO_SWIN_WIDGETNUM(addr);
	} else {
		if (BWIN_WINDOWNUM(addr)) {
			itte = flush_nasid_list->iio_itte[BWIN_WINDOWNUM(addr)];
			wid_num = IIO_ITTE_WIDGET(itte);
		} else
			wid_num = SWIN_WIDGETNUM(addr);
	}
	if (flush_nasid_list->widget_p[wid_num] == NULL)
		return;
	p = &flush_nasid_list->widget_p[wid_num][0];

	/* find a matching BAR */
	for (i = 0; i < DEV_PER_WIDGET; i++,p++) {
		common = p->common;
		for (j = 0; j < PCI_ROM_RESOURCE; j++) {
			if (common->sfdl_bar_list[j].start == 0)
				break;
			if (addr >= common->sfdl_bar_list[j].start
			    && addr <= common->sfdl_bar_list[j].end)
				break;
		}
		if (j < PCI_ROM_RESOURCE && common->sfdl_bar_list[j].start != 0)
			break;
	}

	/* if no matching BAR, return without doing anything. */
	if (i == DEV_PER_WIDGET)
		return;

	/*
	 * For TIOCP use the Device(x) Write Request Buffer Flush Bridge
	 * register since it ensures the data has entered the coherence
	 * domain, unlike PIC.
	 */
	if (is_tio) {
		/*
	 	 * Note:  devices behind TIOCE should never be matched in the
		 * above code, and so the following code is PIC/CP centric.
		 * If CE ever needs the sn_dma_flush mechanism, we will have
		 * to account for that here and in tioce_bus_fixup().
	 	 */
		u32 tio_id = HUB_L(TIO_IOSPACE_ADDR(nasid, TIO_NODE_ID));
		u32 revnum = XWIDGET_PART_REV_NUM(tio_id);

		/* TIOCP BRINGUP WAR (PV907516): Don't write buffer flush reg */
		if ((1 << XWIDGET_PART_REV_NUM_REV(revnum)) & PV907516) {
			return;
		} else {
			pcireg_wrb_flush_get(common->sfdl_pcibus_info,
					     (common->sfdl_slot - 1));
		}
	} else {
		spin_lock_irqsave(&p->sfdl_flush_lock, flags);
		*common->sfdl_flush_addr = 0;

		/* force an interrupt. */
		*(volatile u32 *)(common->sfdl_force_int_addr) = 1;

		/* wait for the interrupt to come back. */
		while (*(common->sfdl_flush_addr) != 0x10f)
			cpu_relax();

		/* okay, everything is synched up. */
		spin_unlock_irqrestore(&p->sfdl_flush_lock, flags);
	}
	return;
}