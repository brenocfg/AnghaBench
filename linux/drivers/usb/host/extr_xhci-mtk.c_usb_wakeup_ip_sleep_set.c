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
typedef  int u32 ;
struct xhci_hcd_mtk {int uwk_vers; int uwk_reg_base; int /*<<< orphan*/  uwk; } ;

/* Variables and functions */
 int PERI_SSUSB_SPM_CTRL ; 
 int PERI_WK_CTRL1 ; 
 int SSC_IP_SLEEP_EN ; 
 int SSC_SPM_INT_EN ; 
#define  SSUSB_UWK_V1 129 
#define  SSUSB_UWK_V2 128 
 int WC1_IS_C (int) ; 
 int WC1_IS_EN ; 
 int WC1_IS_P ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static void usb_wakeup_ip_sleep_set(struct xhci_hcd_mtk *mtk, bool enable)
{
	u32 reg, msk, val;

	switch (mtk->uwk_vers) {
	case SSUSB_UWK_V1:
		reg = mtk->uwk_reg_base + PERI_WK_CTRL1;
		msk = WC1_IS_EN | WC1_IS_C(0xf) | WC1_IS_P;
		val = enable ? (WC1_IS_EN | WC1_IS_C(0x8)) : 0;
		break;
	case SSUSB_UWK_V2:
		reg = mtk->uwk_reg_base + PERI_SSUSB_SPM_CTRL;
		msk = SSC_IP_SLEEP_EN | SSC_SPM_INT_EN;
		val = enable ? msk : 0;
		break;
	default:
		return;
	}
	regmap_update_bits(mtk->uwk, reg, msk, val);
}