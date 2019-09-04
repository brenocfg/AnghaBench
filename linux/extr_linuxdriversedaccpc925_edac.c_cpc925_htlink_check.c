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
struct edac_device_ctl_info {int /*<<< orphan*/  ctl_name; struct cpc925_dev_info* pvt_info; } ;
struct cpc925_dev_info {scalar_t__ vbase; } ;

/* Variables and functions */
 int BRGCTRL_DETSERR ; 
 int BRGCTRL_SECBUSRESET ; 
 int ERRCTRL_CHN_FAL ; 
 int ERRCTRL_RSP_ERR ; 
 int HT_ERRCTRL_DETECTED ; 
 int HT_LINKCTRL_DETECTED ; 
 int HT_LINKERR_DETECTED ; 
 int /*<<< orphan*/  KERN_INFO ; 
 scalar_t__ REG_BRGCTRL_OFFSET ; 
 scalar_t__ REG_ERRCTRL_OFFSET ; 
 scalar_t__ REG_LINKCTRL_OFFSET ; 
 scalar_t__ REG_LINKERR_OFFSET ; 
 int __raw_readl (scalar_t__) ; 
 int /*<<< orphan*/  __raw_writel (int,scalar_t__) ; 
 int /*<<< orphan*/  cpc925_printk (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  edac_device_handle_ce (struct edac_device_ctl_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cpc925_htlink_check(struct edac_device_ctl_info *edac_dev)
{
	struct cpc925_dev_info *dev_info = edac_dev->pvt_info;
	u32 brgctrl = __raw_readl(dev_info->vbase + REG_BRGCTRL_OFFSET);
	u32 linkctrl = __raw_readl(dev_info->vbase + REG_LINKCTRL_OFFSET);
	u32 errctrl = __raw_readl(dev_info->vbase + REG_ERRCTRL_OFFSET);
	u32 linkerr = __raw_readl(dev_info->vbase + REG_LINKERR_OFFSET);

	if (!((brgctrl & BRGCTRL_DETSERR) ||
	      (linkctrl & HT_LINKCTRL_DETECTED) ||
	      (errctrl & HT_ERRCTRL_DETECTED) ||
	      (linkerr & HT_LINKERR_DETECTED)))
		return;

	cpc925_printk(KERN_INFO, "HT Link Fault\n"
				 "HT register dump:\n");
	cpc925_printk(KERN_INFO, "Bridge Ctrl			0x%08x\n",
		      brgctrl);
	cpc925_printk(KERN_INFO, "Link Config Ctrl		0x%08x\n",
		      linkctrl);
	cpc925_printk(KERN_INFO, "Error Enum and Ctrl		0x%08x\n",
		      errctrl);
	cpc925_printk(KERN_INFO, "Link Error			0x%08x\n",
		      linkerr);

	/* Clear by write 1 */
	if (brgctrl & BRGCTRL_DETSERR)
		__raw_writel(BRGCTRL_DETSERR,
				dev_info->vbase + REG_BRGCTRL_OFFSET);

	if (linkctrl & HT_LINKCTRL_DETECTED)
		__raw_writel(HT_LINKCTRL_DETECTED,
				dev_info->vbase + REG_LINKCTRL_OFFSET);

	/* Initiate Secondary Bus Reset to clear the chain failure */
	if (errctrl & ERRCTRL_CHN_FAL)
		__raw_writel(BRGCTRL_SECBUSRESET,
				dev_info->vbase + REG_BRGCTRL_OFFSET);

	if (errctrl & ERRCTRL_RSP_ERR)
		__raw_writel(ERRCTRL_RSP_ERR,
				dev_info->vbase + REG_ERRCTRL_OFFSET);

	if (linkerr & HT_LINKERR_DETECTED)
		__raw_writel(HT_LINKERR_DETECTED,
				dev_info->vbase + REG_LINKERR_OFFSET);

	edac_device_handle_ce(edac_dev, 0, 0, edac_dev->ctl_name);
}