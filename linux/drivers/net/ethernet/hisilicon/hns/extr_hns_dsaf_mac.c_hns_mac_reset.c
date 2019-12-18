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
struct mac_driver {int /*<<< orphan*/  (* mac_pausefrm_cfg ) (struct mac_driver*,int,int) ;int /*<<< orphan*/  (* set_an_mode ) (struct mac_driver*,int) ;int /*<<< orphan*/  (* set_tx_auto_pause_frames ) (struct mac_driver*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* config_max_frame_length ) (struct mac_driver*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* mac_init ) (struct mac_driver*) ;} ;
struct hns_mac_cb {scalar_t__ mac_type; int /*<<< orphan*/  tx_pause_frm_time; int /*<<< orphan*/  max_frm; TYPE_1__* dsaf_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dsaf_ver; } ;

/* Variables and functions */
 int AE_IS_VER1 (int /*<<< orphan*/ ) ; 
 scalar_t__ HNAE_PORT_DEBUG ; 
 struct mac_driver* hns_mac_get_drv (struct hns_mac_cb*) ; 
 int /*<<< orphan*/  stub1 (struct mac_driver*) ; 
 int /*<<< orphan*/  stub2 (struct mac_driver*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct mac_driver*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (struct mac_driver*,int) ; 
 int /*<<< orphan*/  stub5 (struct mac_driver*,int,int) ; 
 int /*<<< orphan*/  stub6 (struct mac_driver*,int,int) ; 

void hns_mac_reset(struct hns_mac_cb *mac_cb)
{
	struct mac_driver *drv = hns_mac_get_drv(mac_cb);
	bool is_ver1 = AE_IS_VER1(mac_cb->dsaf_dev->dsaf_ver);

	drv->mac_init(drv);

	if (drv->config_max_frame_length)
		drv->config_max_frame_length(drv, mac_cb->max_frm);

	if (drv->set_tx_auto_pause_frames)
		drv->set_tx_auto_pause_frames(drv, mac_cb->tx_pause_frm_time);

	if (drv->set_an_mode)
		drv->set_an_mode(drv, 1);

	if (drv->mac_pausefrm_cfg) {
		if (mac_cb->mac_type == HNAE_PORT_DEBUG)
			drv->mac_pausefrm_cfg(drv, !is_ver1, !is_ver1);
		else /* mac rx must disable, dsaf pfc close instead of it*/
			drv->mac_pausefrm_cfg(drv, 0, 1);
	}
}