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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct net_device {int dummy; } ;
struct ionic_lif {struct ionic* ionic; } ;
struct ionic_dev {TYPE_3__* port_info; } ;
struct ionic {int /*<<< orphan*/  dev_cmd_lock; struct ionic_dev idev; } ;
struct TYPE_4__ {scalar_t__ autoneg; scalar_t__ speed; } ;
struct ethtool_link_ksettings {TYPE_1__ base; } ;
struct TYPE_5__ {scalar_t__ an_enable; scalar_t__ fec_type; int /*<<< orphan*/  speed; } ;
struct TYPE_6__ {TYPE_2__ config; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVCMD_TIMEOUT ; 
 int EINVAL ; 
 int /*<<< orphan*/  FEC_BASER ; 
 int /*<<< orphan*/  FEC_RS ; 
 scalar_t__ IONIC_PORT_FEC_TYPE_FC ; 
 scalar_t__ IONIC_PORT_FEC_TYPE_NONE ; 
 scalar_t__ IONIC_PORT_FEC_TYPE_RS ; 
 int /*<<< orphan*/  advertising ; 
 int ethtool_link_ksettings_test_link_mode (struct ethtool_link_ksettings const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ionic_dev_cmd_port_autoneg (struct ionic_dev*,scalar_t__) ; 
 int /*<<< orphan*/  ionic_dev_cmd_port_fec (struct ionic_dev*,scalar_t__) ; 
 int /*<<< orphan*/  ionic_dev_cmd_port_speed (struct ionic_dev*,scalar_t__) ; 
 int ionic_dev_cmd_wait (struct ionic*,int /*<<< orphan*/ ) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*) ; 
 struct ionic_lif* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int ionic_set_link_ksettings(struct net_device *netdev,
				    const struct ethtool_link_ksettings *ks)
{
	struct ionic_lif *lif = netdev_priv(netdev);
	struct ionic *ionic = lif->ionic;
	struct ionic_dev *idev;
	u32 req_rs, req_fc;
	u8 fec_type;
	int err = 0;

	idev = &lif->ionic->idev;
	fec_type = IONIC_PORT_FEC_TYPE_NONE;

	/* set autoneg */
	if (ks->base.autoneg != idev->port_info->config.an_enable) {
		mutex_lock(&ionic->dev_cmd_lock);
		ionic_dev_cmd_port_autoneg(idev, ks->base.autoneg);
		err = ionic_dev_cmd_wait(ionic, DEVCMD_TIMEOUT);
		mutex_unlock(&ionic->dev_cmd_lock);
		if (err)
			return err;
	}

	/* set speed */
	if (ks->base.speed != le32_to_cpu(idev->port_info->config.speed)) {
		mutex_lock(&ionic->dev_cmd_lock);
		ionic_dev_cmd_port_speed(idev, ks->base.speed);
		err = ionic_dev_cmd_wait(ionic, DEVCMD_TIMEOUT);
		mutex_unlock(&ionic->dev_cmd_lock);
		if (err)
			return err;
	}

	/* set FEC */
	req_rs = ethtool_link_ksettings_test_link_mode(ks, advertising, FEC_RS);
	req_fc = ethtool_link_ksettings_test_link_mode(ks, advertising, FEC_BASER);
	if (req_rs && req_fc) {
		netdev_info(netdev, "Only select one FEC mode at a time\n");
		return -EINVAL;
	} else if (req_fc) {
		fec_type = IONIC_PORT_FEC_TYPE_FC;
	} else if (req_rs) {
		fec_type = IONIC_PORT_FEC_TYPE_RS;
	} else if (!(req_rs | req_fc)) {
		fec_type = IONIC_PORT_FEC_TYPE_NONE;
	}

	if (fec_type != idev->port_info->config.fec_type) {
		mutex_lock(&ionic->dev_cmd_lock);
		ionic_dev_cmd_port_fec(idev, fec_type);
		err = ionic_dev_cmd_wait(ionic, DEVCMD_TIMEOUT);
		mutex_unlock(&ionic->dev_cmd_lock);
		if (err)
			return err;
	}

	return 0;
}