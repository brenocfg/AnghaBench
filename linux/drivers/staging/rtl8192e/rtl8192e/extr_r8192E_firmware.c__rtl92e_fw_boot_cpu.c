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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_GEN ; 
 int /*<<< orphan*/  CPU_GEN_BOOT_RDY ; 
 int /*<<< orphan*/  CPU_GEN_PUT_CODE_OK ; 
 int CPU_GEN_PWR_STB_CPU ; 
 int /*<<< orphan*/  _rtl92e_wait_for_fw (struct net_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  netdev_dbg (struct net_device*,char*) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 int rtl92e_readl (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl92e_writeb (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool _rtl92e_fw_boot_cpu(struct net_device *dev)
{
	u32		CPU_status = 0;

	if (!_rtl92e_wait_for_fw(dev, CPU_GEN_PUT_CODE_OK, 200)) {
		netdev_err(dev, "Firmware download failed.\n");
		return false;
	}
	netdev_dbg(dev, "Download Firmware: Put code ok!\n");

	CPU_status = rtl92e_readl(dev, CPU_GEN);
	rtl92e_writeb(dev, CPU_GEN,
		      (u8)((CPU_status|CPU_GEN_PWR_STB_CPU)&0xff));
	mdelay(1);

	if (!_rtl92e_wait_for_fw(dev, CPU_GEN_BOOT_RDY, 200)) {
		netdev_err(dev, "Firmware boot failed.\n");
		return false;
	}

	netdev_dbg(dev, "Download Firmware: Boot ready!\n");

	return true;
}