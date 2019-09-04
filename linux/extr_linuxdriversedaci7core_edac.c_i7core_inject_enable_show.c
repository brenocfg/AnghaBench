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
struct mem_ctl_info {struct i7core_pvt* pvt_info; } ;
struct TYPE_2__ {size_t channel; int enable; } ;
struct i7core_pvt {TYPE_1__ inject; int /*<<< orphan*/ ** pci_ch; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  MC_CHANNEL_ERROR_INJECT ; 
 int /*<<< orphan*/  edac_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  pci_read_config_dword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 struct mem_ctl_info* to_mci (struct device*) ; 

__attribute__((used)) static ssize_t i7core_inject_enable_show(struct device *dev,
					 struct device_attribute *mattr,
					 char *data)
{
	struct mem_ctl_info *mci = to_mci(dev);
	struct i7core_pvt *pvt = mci->pvt_info;
	u32 injectmask;

	if (!pvt->pci_ch[pvt->inject.channel][0])
		return 0;

	pci_read_config_dword(pvt->pci_ch[pvt->inject.channel][0],
			       MC_CHANNEL_ERROR_INJECT, &injectmask);

	edac_dbg(0, "Inject error read: 0x%018x\n", injectmask);

	if (injectmask & 0x0c)
		pvt->inject.enable = 1;

	return sprintf(data, "%d\n", pvt->inject.enable);
}