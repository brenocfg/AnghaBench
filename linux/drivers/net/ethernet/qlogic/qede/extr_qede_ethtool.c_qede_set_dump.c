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
struct TYPE_4__ {int cmd; scalar_t__ num_args; int* args; } ;
struct qede_dev {int /*<<< orphan*/  cdev; TYPE_3__* ops; TYPE_1__ dump_info; } ;
struct net_device {int dummy; } ;
struct ethtool_dump {int flag; } ;
struct TYPE_6__ {TYPE_2__* common; } ;
struct TYPE_5__ {int (* set_grc_config ) (int /*<<< orphan*/ ,int,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DP_ERR (struct qede_dev*,char*,int) ; 
 int EINVAL ; 
#define  QEDE_DUMP_CMD_GRCDUMP 129 
 int QEDE_DUMP_CMD_MAX ; 
 int QEDE_DUMP_CMD_NONE ; 
#define  QEDE_DUMP_CMD_NVM_CFG 128 
 scalar_t__ QEDE_DUMP_MAX_ARGS ; 
 struct qede_dev* netdev_priv (struct net_device*) ; 
 int stub1 (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int qede_set_dump(struct net_device *dev, struct ethtool_dump *val)
{
	struct qede_dev *edev = netdev_priv(dev);
	int rc = 0;

	if (edev->dump_info.cmd == QEDE_DUMP_CMD_NONE) {
		if (val->flag > QEDE_DUMP_CMD_MAX) {
			DP_ERR(edev, "Invalid command %d\n", val->flag);
			return -EINVAL;
		}
		edev->dump_info.cmd = val->flag;
		edev->dump_info.num_args = 0;
		return 0;
	}

	if (edev->dump_info.num_args == QEDE_DUMP_MAX_ARGS) {
		DP_ERR(edev, "Arg count = %d\n", edev->dump_info.num_args);
		return -EINVAL;
	}

	switch (edev->dump_info.cmd) {
	case QEDE_DUMP_CMD_NVM_CFG:
		edev->dump_info.args[edev->dump_info.num_args] = val->flag;
		edev->dump_info.num_args++;
		break;
	case QEDE_DUMP_CMD_GRCDUMP:
		rc = edev->ops->common->set_grc_config(edev->cdev,
						       val->flag, 1);
		break;
	default:
		break;
	}

	return rc;
}