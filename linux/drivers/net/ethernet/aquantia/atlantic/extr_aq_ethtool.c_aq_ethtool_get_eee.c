#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int dummy; } ;
struct ethtool_eee {int supported; int advertised; int lp_advertised; int eee_enabled; int tx_lpi_enabled; int eee_active; } ;
struct TYPE_4__ {scalar_t__ eee_speeds; } ;
struct aq_nic_s {TYPE_2__ aq_nic_cfg; int /*<<< orphan*/  fwreq_mutex; int /*<<< orphan*/  aq_hw; TYPE_1__* aq_fw_ops; } ;
struct TYPE_3__ {int (* get_eee_rate ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 void* eee_mask_to_ethtool_mask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct aq_nic_s* netdev_priv (struct net_device*) ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int aq_ethtool_get_eee(struct net_device *ndev, struct ethtool_eee *eee)
{
	struct aq_nic_s *aq_nic = netdev_priv(ndev);
	u32 rate, supported_rates;
	int err = 0;

	if (!aq_nic->aq_fw_ops->get_eee_rate)
		return -EOPNOTSUPP;

	mutex_lock(&aq_nic->fwreq_mutex);
	err = aq_nic->aq_fw_ops->get_eee_rate(aq_nic->aq_hw, &rate,
					      &supported_rates);
	mutex_unlock(&aq_nic->fwreq_mutex);
	if (err < 0)
		return err;

	eee->supported = eee_mask_to_ethtool_mask(supported_rates);

	if (aq_nic->aq_nic_cfg.eee_speeds)
		eee->advertised = eee->supported;

	eee->lp_advertised = eee_mask_to_ethtool_mask(rate);

	eee->eee_enabled = !!eee->advertised;

	eee->tx_lpi_enabled = eee->eee_enabled;
	if (eee->advertised & eee->lp_advertised)
		eee->eee_active = true;

	return 0;
}