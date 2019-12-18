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
struct rtw_pci {int* irq_mask; int /*<<< orphan*/  irq_lock; } ;
struct rtw_dev {scalar_t__ priv; } ;

/* Variables and functions */
 int IMR_BCNDMAINT_E ; 
 int IMR_BEDOK ; 
 int IMR_BKDOK ; 
 int IMR_H2CDOK ; 
 int IMR_HIGHDOK ; 
 int IMR_MGNTDOK ; 
 int IMR_ROK ; 
 int IMR_TXFOVW ; 
 int IMR_VIDOK ; 
 int IMR_VODOK ; 
 int rtw_pci_init_trx_ring (struct rtw_dev*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rtw_pci_init(struct rtw_dev *rtwdev)
{
	struct rtw_pci *rtwpci = (struct rtw_pci *)rtwdev->priv;
	int ret = 0;

	rtwpci->irq_mask[0] = IMR_HIGHDOK |
			      IMR_MGNTDOK |
			      IMR_BKDOK |
			      IMR_BEDOK |
			      IMR_VIDOK |
			      IMR_VODOK |
			      IMR_ROK |
			      IMR_BCNDMAINT_E |
			      0;
	rtwpci->irq_mask[1] = IMR_TXFOVW |
			      0;
	rtwpci->irq_mask[3] = IMR_H2CDOK |
			      0;
	spin_lock_init(&rtwpci->irq_lock);
	ret = rtw_pci_init_trx_ring(rtwdev);

	return ret;
}