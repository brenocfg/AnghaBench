#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int cmd; int /*<<< orphan*/ * args; } ;
struct qede_dev {TYPE_3__ dump_info; int /*<<< orphan*/  cdev; TYPE_2__* ops; } ;
struct net_device {int dummy; } ;
struct ethtool_dump {int flag; int /*<<< orphan*/  len; int /*<<< orphan*/  version; } ;
struct TYPE_5__ {TYPE_1__* common; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* dbg_all_data_size ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* read_nvm_cfg_len ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DP_ERR (struct qede_dev*,char*,...) ; 
 int /*<<< orphan*/  DP_VERBOSE (struct qede_dev*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
#define  QEDE_DUMP_CMD_GRCDUMP 129 
#define  QEDE_DUMP_CMD_NVM_CFG 128 
 int /*<<< orphan*/  QEDE_DUMP_VERSION ; 
 int /*<<< orphan*/  QED_MSG_DEBUG ; 
 struct qede_dev* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qede_get_dump_flag(struct net_device *dev,
			      struct ethtool_dump *dump)
{
	struct qede_dev *edev = netdev_priv(dev);

	if (!edev->ops || !edev->ops->common) {
		DP_ERR(edev, "Edev ops not populated\n");
		return -EINVAL;
	}

	dump->version = QEDE_DUMP_VERSION;
	switch (edev->dump_info.cmd) {
	case QEDE_DUMP_CMD_NVM_CFG:
		dump->flag = QEDE_DUMP_CMD_NVM_CFG;
		dump->len = edev->ops->common->read_nvm_cfg_len(edev->cdev,
						edev->dump_info.args[0]);
		break;
	case QEDE_DUMP_CMD_GRCDUMP:
		dump->flag = QEDE_DUMP_CMD_GRCDUMP;
		dump->len = edev->ops->common->dbg_all_data_size(edev->cdev);
		break;
	default:
		DP_ERR(edev, "Invalid cmd = %d\n", edev->dump_info.cmd);
		return -EINVAL;
	}

	DP_VERBOSE(edev, QED_MSG_DEBUG,
		   "dump->version = 0x%x dump->flag = %d dump->len = %d\n",
		   dump->version, dump->flag, dump->len);
	return 0;
}