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
typedef  int u8 ;
struct pcf50633_mbc {scalar_t__ adapter_online; scalar_t__ usb_online; int /*<<< orphan*/  pcf; } ;
struct pcf50633 {int /*<<< orphan*/  mbc_pdev; } ;

/* Variables and functions */
 int PCF50633_MBCS2_MBC_ADP_FAST ; 
 int PCF50633_MBCS2_MBC_ADP_FAST_WAIT ; 
 int PCF50633_MBCS2_MBC_ADP_PRE ; 
 int PCF50633_MBCS2_MBC_ADP_PRE_WAIT ; 
 int PCF50633_MBCS2_MBC_MASK ; 
 int PCF50633_MBCS2_MBC_USB_FAST ; 
 int PCF50633_MBCS2_MBC_USB_FAST_WAIT ; 
 int PCF50633_MBCS2_MBC_USB_PRE ; 
 int PCF50633_MBCS2_MBC_USB_PRE_WAIT ; 
 int PCF50633_MBC_ADAPTER_ACTIVE ; 
 int PCF50633_MBC_ADAPTER_ONLINE ; 
 int PCF50633_MBC_USB_ACTIVE ; 
 int PCF50633_MBC_USB_ONLINE ; 
 int /*<<< orphan*/  PCF50633_REG_MBCS2 ; 
 int pcf50633_reg_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct pcf50633_mbc* platform_get_drvdata (int /*<<< orphan*/ ) ; 

int pcf50633_mbc_get_status(struct pcf50633 *pcf)
{
	struct pcf50633_mbc *mbc  = platform_get_drvdata(pcf->mbc_pdev);
	int status = 0;
	u8 chgmod;

	if (!mbc)
		return 0;

	chgmod = pcf50633_reg_read(mbc->pcf, PCF50633_REG_MBCS2)
		& PCF50633_MBCS2_MBC_MASK;

	if (mbc->usb_online)
		status |= PCF50633_MBC_USB_ONLINE;
	if (chgmod == PCF50633_MBCS2_MBC_USB_PRE ||
	    chgmod == PCF50633_MBCS2_MBC_USB_PRE_WAIT ||
	    chgmod == PCF50633_MBCS2_MBC_USB_FAST ||
	    chgmod == PCF50633_MBCS2_MBC_USB_FAST_WAIT)
		status |= PCF50633_MBC_USB_ACTIVE;
	if (mbc->adapter_online)
		status |= PCF50633_MBC_ADAPTER_ONLINE;
	if (chgmod == PCF50633_MBCS2_MBC_ADP_PRE ||
	    chgmod == PCF50633_MBCS2_MBC_ADP_PRE_WAIT ||
	    chgmod == PCF50633_MBCS2_MBC_ADP_FAST ||
	    chgmod == PCF50633_MBCS2_MBC_ADP_FAST_WAIT)
		status |= PCF50633_MBC_ADAPTER_ACTIVE;

	return status;
}