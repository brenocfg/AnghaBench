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
struct qlcnic_fw_dump {int /*<<< orphan*/  tmpl_hdr; int /*<<< orphan*/  clr; } ;
struct qlcnic_adapter {int /*<<< orphan*/  state; int /*<<< orphan*/  flags; TYPE_1__* ahw; } ;
struct net_device {int dummy; } ;
struct ethtool_dump {int flag; } ;
struct TYPE_2__ {struct qlcnic_fw_dump fw_dump; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
#define  QLCNIC_DISABLE_FW_DUMP 133 
#define  QLCNIC_ENABLE_FW_DUMP 132 
#define  QLCNIC_FORCE_FW_DUMP_KEY 131 
#define  QLCNIC_FORCE_FW_RESET 130 
 int /*<<< orphan*/  QLCNIC_FW_RESET_OWNER ; 
#define  QLCNIC_RESET_QUIESCENT 129 
#define  QLCNIC_SET_QUIESCENT 128 
 int /*<<< orphan*/  __QLCNIC_MAINTENANCE_MODE ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*,...) ; 
 struct qlcnic_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  qlcnic_check_fw_dump_state (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_dev_request_reset (struct qlcnic_adapter*,int) ; 
 int qlcnic_disable_fw_dump_state (struct qlcnic_adapter*) ; 
 int qlcnic_enable_fw_dump_state (struct qlcnic_adapter*) ; 
 int* qlcnic_fw_dump_level ; 
 int qlcnic_set_dump_mask (struct qlcnic_adapter*,int) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
qlcnic_set_dump(struct net_device *netdev, struct ethtool_dump *val)
{
	struct qlcnic_adapter *adapter = netdev_priv(netdev);
	struct qlcnic_fw_dump *fw_dump = &adapter->ahw->fw_dump;
	bool valid_mask = false;
	int i, ret = 0;

	switch (val->flag) {
	case QLCNIC_FORCE_FW_DUMP_KEY:
		if (!fw_dump->tmpl_hdr) {
			netdev_err(netdev, "FW dump not supported\n");
			ret = -EOPNOTSUPP;
			break;
		}

		if (!qlcnic_check_fw_dump_state(adapter)) {
			netdev_info(netdev, "FW dump not enabled\n");
			ret = -EOPNOTSUPP;
			break;
		}

		if (fw_dump->clr) {
			netdev_info(netdev,
				    "Previous dump not cleared, not forcing dump\n");
			break;
		}

		netdev_info(netdev, "Forcing a FW dump\n");
		qlcnic_dev_request_reset(adapter, val->flag);
		break;
	case QLCNIC_DISABLE_FW_DUMP:
		if (!fw_dump->tmpl_hdr) {
			netdev_err(netdev, "FW dump not supported\n");
			ret = -EOPNOTSUPP;
			break;
		}

		ret = qlcnic_disable_fw_dump_state(adapter);
		break;

	case QLCNIC_ENABLE_FW_DUMP:
		if (!fw_dump->tmpl_hdr) {
			netdev_err(netdev, "FW dump not supported\n");
			ret = -EOPNOTSUPP;
			break;
		}

		ret = qlcnic_enable_fw_dump_state(adapter);
		break;

	case QLCNIC_FORCE_FW_RESET:
		netdev_info(netdev, "Forcing a FW reset\n");
		qlcnic_dev_request_reset(adapter, val->flag);
		adapter->flags &= ~QLCNIC_FW_RESET_OWNER;
		break;

	case QLCNIC_SET_QUIESCENT:
	case QLCNIC_RESET_QUIESCENT:
		if (test_bit(__QLCNIC_MAINTENANCE_MODE, &adapter->state))
			netdev_info(netdev, "Device is in non-operational state\n");
		break;

	default:
		if (!fw_dump->tmpl_hdr) {
			netdev_err(netdev, "FW dump not supported\n");
			ret = -EOPNOTSUPP;
			break;
		}

		for (i = 0; i < ARRAY_SIZE(qlcnic_fw_dump_level); i++) {
			if (val->flag == qlcnic_fw_dump_level[i]) {
				valid_mask = true;
				break;
			}
		}

		if (valid_mask) {
			ret = qlcnic_set_dump_mask(adapter, val->flag);
		} else {
			netdev_info(netdev, "Invalid dump level: 0x%x\n",
				    val->flag);
			ret = -EINVAL;
		}
	}
	return ret;
}