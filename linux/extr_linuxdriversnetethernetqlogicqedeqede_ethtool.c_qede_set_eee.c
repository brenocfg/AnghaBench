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
struct qede_dev {int /*<<< orphan*/  cdev; TYPE_3__* ops; } ;
struct TYPE_4__ {int /*<<< orphan*/  tx_lpi_timer; int /*<<< orphan*/  tx_lpi_enable; int /*<<< orphan*/  enable; int /*<<< orphan*/  adv_caps; } ;
struct qed_link_params {int link_up; TYPE_1__ eee; int /*<<< orphan*/  override_flags; int /*<<< orphan*/  eee_supported; } ;
struct qed_link_output {int link_up; TYPE_1__ eee; int /*<<< orphan*/  override_flags; int /*<<< orphan*/  eee_supported; } ;
struct net_device {int dummy; } ;
struct ethtool_eee {int advertised; int /*<<< orphan*/  tx_lpi_timer; int /*<<< orphan*/  tx_lpi_enabled; int /*<<< orphan*/  eee_enabled; } ;
typedef  int /*<<< orphan*/  params ;
typedef  int /*<<< orphan*/  current_link ;
struct TYPE_6__ {TYPE_2__* common; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* set_link ) (int /*<<< orphan*/ ,struct qed_link_params*) ;int /*<<< orphan*/  (* get_link ) (int /*<<< orphan*/ ,struct qed_link_params*) ;int /*<<< orphan*/  (* can_link_change ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int ADVERTISED_10000baseT_Full ; 
 int ADVERTISED_1000baseT_Full ; 
 int /*<<< orphan*/  DP_INFO (struct qede_dev*,char*) ; 
 int /*<<< orphan*/  DP_VERBOSE (struct qede_dev*,int /*<<< orphan*/ ,char*,int) ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  QED_EEE_10G_ADV ; 
 int /*<<< orphan*/  QED_EEE_1G_ADV ; 
 int /*<<< orphan*/  QED_LINK_OVERRIDE_EEE_CONFIG ; 
 int /*<<< orphan*/  QED_MSG_DEBUG ; 
 int /*<<< orphan*/  memset (struct qed_link_params*,int /*<<< orphan*/ ,int) ; 
 struct qede_dev* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,struct qed_link_params*) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,struct qed_link_params*) ; 

__attribute__((used)) static int qede_set_eee(struct net_device *dev, struct ethtool_eee *edata)
{
	struct qede_dev *edev = netdev_priv(dev);
	struct qed_link_output current_link;
	struct qed_link_params params;

	if (!edev->ops->common->can_link_change(edev->cdev)) {
		DP_INFO(edev, "Link settings are not allowed to be changed\n");
		return -EOPNOTSUPP;
	}

	memset(&current_link, 0, sizeof(current_link));
	edev->ops->common->get_link(edev->cdev, &current_link);

	if (!current_link.eee_supported) {
		DP_INFO(edev, "EEE is not supported\n");
		return -EOPNOTSUPP;
	}

	memset(&params, 0, sizeof(params));
	params.override_flags |= QED_LINK_OVERRIDE_EEE_CONFIG;

	if (!(edata->advertised & (ADVERTISED_1000baseT_Full |
				   ADVERTISED_10000baseT_Full)) ||
	    ((edata->advertised & (ADVERTISED_1000baseT_Full |
				   ADVERTISED_10000baseT_Full)) !=
	     edata->advertised)) {
		DP_VERBOSE(edev, QED_MSG_DEBUG,
			   "Invalid advertised capabilities %d\n",
			   edata->advertised);
		return -EINVAL;
	}

	if (edata->advertised & ADVERTISED_1000baseT_Full)
		params.eee.adv_caps = QED_EEE_1G_ADV;
	if (edata->advertised & ADVERTISED_10000baseT_Full)
		params.eee.adv_caps |= QED_EEE_10G_ADV;
	params.eee.enable = edata->eee_enabled;
	params.eee.tx_lpi_enable = edata->tx_lpi_enabled;
	params.eee.tx_lpi_timer = edata->tx_lpi_timer;

	params.link_up = true;
	edev->ops->common->set_link(edev->cdev, &params);

	return 0;
}