#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int dummy; } ;
struct ionic_lif {TYPE_4__* ionic; } ;
struct ethtool_regs {int /*<<< orphan*/  version; } ;
struct TYPE_7__ {TYPE_1__* dev_cmd_regs; TYPE_2__* dev_info_regs; } ;
struct TYPE_8__ {TYPE_3__ idev; } ;
struct TYPE_6__ {int /*<<< orphan*/  words; } ;
struct TYPE_5__ {int /*<<< orphan*/  words; } ;

/* Variables and functions */
 int IONIC_DEV_CMD_REG_COUNT ; 
 int /*<<< orphan*/  IONIC_DEV_CMD_REG_VERSION ; 
 int IONIC_DEV_INFO_REG_COUNT ; 
 int /*<<< orphan*/  memcpy_fromio (void*,int /*<<< orphan*/ ,unsigned int) ; 
 struct ionic_lif* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void ionic_get_regs(struct net_device *netdev, struct ethtool_regs *regs,
			   void *p)
{
	struct ionic_lif *lif = netdev_priv(netdev);
	unsigned int size;

	regs->version = IONIC_DEV_CMD_REG_VERSION;

	size = IONIC_DEV_INFO_REG_COUNT * sizeof(u32);
	memcpy_fromio(p, lif->ionic->idev.dev_info_regs->words, size);

	size = IONIC_DEV_CMD_REG_COUNT * sizeof(u32);
	memcpy_fromio(p, lif->ionic->idev.dev_cmd_regs->words, size);
}