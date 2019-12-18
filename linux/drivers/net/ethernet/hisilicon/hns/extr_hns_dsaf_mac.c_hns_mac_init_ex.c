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
struct mac_params {int /*<<< orphan*/  mac_mode; } ;
struct mac_driver {int /*<<< orphan*/  (* mac_free ) (int /*<<< orphan*/ *) ;} ;
struct TYPE_2__ {int /*<<< orphan*/ * mac; } ;
struct hns_mac_cb {TYPE_1__ priv; int /*<<< orphan*/  mac_id; int /*<<< orphan*/  half_duplex; int /*<<< orphan*/  speed; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ MAC_SPEED_10000 ; 
 scalar_t__ MAC_SPEED_FROM_MODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hns_dsaf_fix_mac_mode (struct hns_mac_cb*) ; 
 scalar_t__ hns_gmac_config (struct hns_mac_cb*,struct mac_params*) ; 
 int /*<<< orphan*/  hns_mac_adjust_link (struct hns_mac_cb*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hns_mac_param_get (struct mac_params*,struct hns_mac_cb*) ; 
 int hns_mac_port_config_bc_en (struct hns_mac_cb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hns_mac_reset (struct hns_mac_cb*) ; 
 scalar_t__ hns_xgmac_config (struct hns_mac_cb*,struct mac_params*) ; 
 int /*<<< orphan*/  memset (struct mac_params*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hns_mac_init_ex(struct hns_mac_cb *mac_cb)
{
	int ret;
	struct mac_params param;
	struct mac_driver *drv;

	hns_dsaf_fix_mac_mode(mac_cb);

	memset(&param, 0, sizeof(struct mac_params));
	hns_mac_param_get(&param, mac_cb);

	if (MAC_SPEED_FROM_MODE(param.mac_mode) < MAC_SPEED_10000)
		drv = (struct mac_driver *)hns_gmac_config(mac_cb, &param);
	else
		drv = (struct mac_driver *)hns_xgmac_config(mac_cb, &param);

	if (!drv)
		return -ENOMEM;

	mac_cb->priv.mac = (void *)drv;
	hns_mac_reset(mac_cb);

	hns_mac_adjust_link(mac_cb, mac_cb->speed, !mac_cb->half_duplex);

	ret = hns_mac_port_config_bc_en(mac_cb, mac_cb->mac_id, 0, true);
	if (ret)
		goto free_mac_drv;

	return 0;

free_mac_drv:
	drv->mac_free(mac_cb->priv.mac);
	mac_cb->priv.mac = NULL;

	return ret;
}