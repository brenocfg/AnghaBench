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
struct mac_priv_s {scalar_t__ max_speed; int /*<<< orphan*/  dev; int /*<<< orphan*/  fixed_link; } ;
struct mac_device {int /*<<< orphan*/  fman_mac; struct mac_priv_s* priv; } ;
struct fman_mac_params {int /*<<< orphan*/  phy_if; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  PHY_INTERFACE_MODE_XGMII ; 
 scalar_t__ SPEED_10000 ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fman_get_max_frm () ; 
 int memac_cfg_fixed_link (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int memac_cfg_max_frame_len (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int memac_cfg_reset_on_init (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memac_config (struct fman_mac_params*) ; 
 int /*<<< orphan*/  memac_free (int /*<<< orphan*/ ) ; 
 int memac_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_fman_mac_params (struct mac_device*,struct fman_mac_params*) ; 

__attribute__((used)) static int memac_initialization(struct mac_device *mac_dev)
{
	int			 err;
	struct mac_priv_s	*priv;
	struct fman_mac_params	 params;

	priv = mac_dev->priv;

	set_fman_mac_params(mac_dev, &params);

	if (priv->max_speed == SPEED_10000)
		params.phy_if = PHY_INTERFACE_MODE_XGMII;

	mac_dev->fman_mac = memac_config(&params);
	if (!mac_dev->fman_mac) {
		err = -EINVAL;
		goto _return;
	}

	err = memac_cfg_max_frame_len(mac_dev->fman_mac, fman_get_max_frm());
	if (err < 0)
		goto _return_fm_mac_free;

	err = memac_cfg_reset_on_init(mac_dev->fman_mac, true);
	if (err < 0)
		goto _return_fm_mac_free;

	err = memac_cfg_fixed_link(mac_dev->fman_mac, priv->fixed_link);
	if (err < 0)
		goto _return_fm_mac_free;

	err = memac_init(mac_dev->fman_mac);
	if (err < 0)
		goto _return_fm_mac_free;

	dev_info(priv->dev, "FMan MEMAC\n");

	goto _return;

_return_fm_mac_free:
	memac_free(mac_dev->fman_mac);

_return:
	return err;
}