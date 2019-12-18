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
typedef  int u32 ;
struct mac_driver {int /*<<< orphan*/  (* get_link_status ) (struct mac_driver*,int*) ;} ;
struct hns_mac_cb {scalar_t__ media_type; int link; TYPE_2__* dsaf_dev; } ;
struct TYPE_4__ {TYPE_1__* misc_op; } ;
struct TYPE_3__ {int (* get_sfp_prsnt ) (struct hns_mac_cb*,int*) ;} ;

/* Variables and functions */
 scalar_t__ HNAE_MEDIA_TYPE_FIBER ; 
 struct mac_driver* hns_mac_get_drv (struct hns_mac_cb*) ; 
 int /*<<< orphan*/  stub1 (struct mac_driver*,int*) ; 
 int stub2 (struct hns_mac_cb*,int*) ; 

void hns_mac_get_link_status(struct hns_mac_cb *mac_cb, u32 *link_status)
{
	struct mac_driver *mac_ctrl_drv;
	int ret, sfp_prsnt;

	mac_ctrl_drv = hns_mac_get_drv(mac_cb);

	if (mac_ctrl_drv->get_link_status)
		mac_ctrl_drv->get_link_status(mac_ctrl_drv, link_status);
	else
		*link_status = 0;

	if (mac_cb->media_type == HNAE_MEDIA_TYPE_FIBER) {
		ret = mac_cb->dsaf_dev->misc_op->get_sfp_prsnt(mac_cb,
							       &sfp_prsnt);
		if (!ret)
			*link_status = *link_status && sfp_prsnt;
	}

	mac_cb->link = *link_status;
}