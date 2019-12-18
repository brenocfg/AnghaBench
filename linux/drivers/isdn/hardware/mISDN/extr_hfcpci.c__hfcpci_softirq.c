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
struct TYPE_2__ {int int_m2; scalar_t__ bswapped; } ;
struct hfc_pci {int /*<<< orphan*/  lock; TYPE_1__ hw; } ;
struct device {int dummy; } ;
struct bchannel {scalar_t__ state; } ;

/* Variables and functions */
 int HFCPCI_IRQ_ENABLE ; 
 scalar_t__ ISDN_P_B_RAW ; 
 struct bchannel* Sel_BCS (struct hfc_pci*,int) ; 
 struct hfc_pci* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  main_rec_hfcpci (struct bchannel*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tx_birq (struct bchannel*) ; 

__attribute__((used)) static int
_hfcpci_softirq(struct device *dev, void *unused)
{
	struct hfc_pci  *hc = dev_get_drvdata(dev);
	struct bchannel *bch;
	if (hc == NULL)
		return 0;

	if (hc->hw.int_m2 & HFCPCI_IRQ_ENABLE) {
		spin_lock(&hc->lock);
		bch = Sel_BCS(hc, hc->hw.bswapped ? 2 : 1);
		if (bch && bch->state == ISDN_P_B_RAW) { /* B1 rx&tx */
			main_rec_hfcpci(bch);
			tx_birq(bch);
		}
		bch = Sel_BCS(hc, hc->hw.bswapped ? 1 : 2);
		if (bch && bch->state == ISDN_P_B_RAW) { /* B2 rx&tx */
			main_rec_hfcpci(bch);
			tx_birq(bch);
		}
		spin_unlock(&hc->lock);
	}
	return 0;
}