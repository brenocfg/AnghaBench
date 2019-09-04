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
struct typhoon {scalar_t__ card_state; struct pci_dev* pdev; } ;
struct resp_desc {int /*<<< orphan*/  parm2; } ;
struct pci_dev {int dummy; } ;
struct net_device {int dummy; } ;
struct ethtool_drvinfo {int /*<<< orphan*/  bus_info; int /*<<< orphan*/  driver; int /*<<< orphan*/  fw_version; } ;
struct cmd_desc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_COMMAND_WITH_RESPONSE (struct cmd_desc*,int /*<<< orphan*/ ) ; 
 char* KBUILD_MODNAME ; 
 scalar_t__ Sleeping ; 
 int /*<<< orphan*/  TYPHOON_CMD_READ_VERSIONS ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 struct typhoon* netdev_priv (struct net_device*) ; 
 char* pci_name (struct pci_dev*) ; 
 int /*<<< orphan*/  smp_rmb () ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int,int,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ typhoon_issue_command (struct typhoon*,int,struct cmd_desc*,int,struct resp_desc*) ; 

__attribute__((used)) static void
typhoon_get_drvinfo(struct net_device *dev, struct ethtool_drvinfo *info)
{
	struct typhoon *tp = netdev_priv(dev);
	struct pci_dev *pci_dev = tp->pdev;
	struct cmd_desc xp_cmd;
	struct resp_desc xp_resp[3];

	smp_rmb();
	if(tp->card_state == Sleeping) {
		strlcpy(info->fw_version, "Sleep image",
			sizeof(info->fw_version));
	} else {
		INIT_COMMAND_WITH_RESPONSE(&xp_cmd, TYPHOON_CMD_READ_VERSIONS);
		if(typhoon_issue_command(tp, 1, &xp_cmd, 3, xp_resp) < 0) {
			strlcpy(info->fw_version, "Unknown runtime",
				sizeof(info->fw_version));
		} else {
			u32 sleep_ver = le32_to_cpu(xp_resp[0].parm2);
			snprintf(info->fw_version, sizeof(info->fw_version),
				"%02x.%03x.%03x", sleep_ver >> 24,
				(sleep_ver >> 12) & 0xfff, sleep_ver & 0xfff);
		}
	}

	strlcpy(info->driver, KBUILD_MODNAME, sizeof(info->driver));
	strlcpy(info->bus_info, pci_name(pci_dev), sizeof(info->bus_info));
}