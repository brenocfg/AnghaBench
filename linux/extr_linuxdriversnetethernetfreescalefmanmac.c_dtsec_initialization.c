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
typedef  int /*<<< orphan*/  u32 ;
struct mac_priv_s {int /*<<< orphan*/  dev; } ;
struct mac_device {int (* set_exception ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  fman_mac; struct mac_priv_s* priv; } ;
struct fman_mac_params {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  FM_MAC_EX_1G_RX_MIB_CNT_OVFL ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int dtsec_cfg_max_frame_len (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dtsec_cfg_pad_and_crc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dtsec_config (struct fman_mac_params*) ; 
 int /*<<< orphan*/  dtsec_free (int /*<<< orphan*/ ) ; 
 int dtsec_get_version (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int dtsec_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fman_get_max_frm () ; 
 int /*<<< orphan*/  set_fman_mac_params (struct mac_device*,struct fman_mac_params*) ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int dtsec_initialization(struct mac_device *mac_dev)
{
	int			err;
	struct mac_priv_s	*priv;
	struct fman_mac_params	params;
	u32			version;

	priv = mac_dev->priv;

	set_fman_mac_params(mac_dev, &params);

	mac_dev->fman_mac = dtsec_config(&params);
	if (!mac_dev->fman_mac) {
		err = -EINVAL;
		goto _return;
	}

	err = dtsec_cfg_max_frame_len(mac_dev->fman_mac, fman_get_max_frm());
	if (err < 0)
		goto _return_fm_mac_free;

	err = dtsec_cfg_pad_and_crc(mac_dev->fman_mac, true);
	if (err < 0)
		goto _return_fm_mac_free;

	err = dtsec_init(mac_dev->fman_mac);
	if (err < 0)
		goto _return_fm_mac_free;

	/* For 1G MAC, disable by default the MIB counters overflow interrupt */
	err = mac_dev->set_exception(mac_dev->fman_mac,
				     FM_MAC_EX_1G_RX_MIB_CNT_OVFL, false);
	if (err < 0)
		goto _return_fm_mac_free;

	err = dtsec_get_version(mac_dev->fman_mac, &version);
	if (err < 0)
		goto _return_fm_mac_free;

	dev_info(priv->dev, "FMan dTSEC version: 0x%08x\n", version);

	goto _return;

_return_fm_mac_free:
	dtsec_free(mac_dev->fman_mac);

_return:
	return err;
}