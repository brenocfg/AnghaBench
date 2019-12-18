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
struct net_device {int dummy; } ;
struct aq_nic_s {int dummy; } ;

/* Variables and functions */
 int aq_filters_vlans_update (struct aq_nic_s*) ; 
 int /*<<< orphan*/  aq_nic_deinit (struct aq_nic_s*) ; 
 int aq_nic_init (struct aq_nic_s*) ; 
 int aq_nic_start (struct aq_nic_s*) ; 
 int aq_reapply_rxnfc_all_rules (struct aq_nic_s*) ; 
 struct aq_nic_s* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int aq_ndev_open(struct net_device *ndev)
{
	int err = 0;
	struct aq_nic_s *aq_nic = netdev_priv(ndev);

	err = aq_nic_init(aq_nic);
	if (err < 0)
		goto err_exit;

	err = aq_reapply_rxnfc_all_rules(aq_nic);
	if (err < 0)
		goto err_exit;

	err = aq_filters_vlans_update(aq_nic);
	if (err < 0)
		goto err_exit;

	err = aq_nic_start(aq_nic);
	if (err < 0)
		goto err_exit;

err_exit:
	if (err < 0)
		aq_nic_deinit(aq_nic);
	return err;
}