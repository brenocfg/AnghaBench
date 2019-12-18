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
typedef  int u32 ;
struct net_device {int dummy; } ;
struct firmware {int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;
struct ethtool_flash {char* data; } ;
struct adapter {unsigned int pf; int flags; unsigned int mbox; int /*<<< orphan*/  pdev_dev; } ;

/* Variables and functions */
 int CXGB4_FULL_INIT_DONE ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  PCIE_FW_A ; 
 unsigned int PCIE_FW_MASTER_G (int) ; 
 int PCIE_FW_MASTER_M ; 
 int PCIE_FW_MASTER_VLD_F ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 struct adapter* netdev2adap (struct net_device*) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int request_firmware (struct firmware const**,char*,int /*<<< orphan*/ ) ; 
 int t4_fw_upgrade (struct adapter*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int t4_read_reg (struct adapter*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int set_flash(struct net_device *netdev, struct ethtool_flash *ef)
{
	int ret;
	const struct firmware *fw;
	struct adapter *adap = netdev2adap(netdev);
	unsigned int mbox = PCIE_FW_MASTER_M + 1;
	u32 pcie_fw;
	unsigned int master;
	u8 master_vld = 0;

	pcie_fw = t4_read_reg(adap, PCIE_FW_A);
	master = PCIE_FW_MASTER_G(pcie_fw);
	if (pcie_fw & PCIE_FW_MASTER_VLD_F)
		master_vld = 1;
	/* if csiostor is the master return */
	if (master_vld && (master != adap->pf)) {
		dev_warn(adap->pdev_dev,
			 "cxgb4 driver needs to be loaded as MASTER to support FW flash\n");
		return -EOPNOTSUPP;
	}

	ef->data[sizeof(ef->data) - 1] = '\0';
	ret = request_firmware(&fw, ef->data, adap->pdev_dev);
	if (ret < 0)
		return ret;

	/* If the adapter has been fully initialized then we'll go ahead and
	 * try to get the firmware's cooperation in upgrading to the new
	 * firmware image otherwise we'll try to do the entire job from the
	 * host ... and we always "force" the operation in this path.
	 */
	if (adap->flags & CXGB4_FULL_INIT_DONE)
		mbox = adap->mbox;

	ret = t4_fw_upgrade(adap, mbox, fw->data, fw->size, 1);
	release_firmware(fw);
	if (!ret)
		dev_info(adap->pdev_dev,
			 "loaded firmware %s, reload cxgb4 driver\n", ef->data);
	return ret;
}