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
struct hns_mac_cb {struct dsaf_device* dsaf_dev; } ;
struct hnae_vf_cb {int /*<<< orphan*/  mac_cb; } ;
struct hnae_handle {int dummy; } ;
struct dsaf_device {TYPE_1__* misc_op; } ;
typedef  enum hnae_loop { ____Placeholder_hnae_loop } hnae_loop ;
struct TYPE_2__ {int (* cfg_serdes_loopback ) (int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int EINVAL ; 
#define  MAC_INTERNALLOOP_MAC 130 
#define  MAC_INTERNALLOOP_PHY 129 
#define  MAC_INTERNALLOOP_SERDES 128 
 struct hnae_vf_cb* hns_ae_get_vf_cb (struct hnae_handle*) ; 
 struct hns_mac_cb* hns_get_mac_cb (struct hnae_handle*) ; 
 int hns_mac_config_mac_loopback (int /*<<< orphan*/ ,int,int) ; 
 int stub1 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int hns_ae_config_loopback(struct hnae_handle *handle,
				  enum hnae_loop loop, int en)
{
	int ret;
	struct hnae_vf_cb *vf_cb = hns_ae_get_vf_cb(handle);
	struct hns_mac_cb *mac_cb = hns_get_mac_cb(handle);
	struct dsaf_device *dsaf_dev = mac_cb->dsaf_dev;

	switch (loop) {
	case MAC_INTERNALLOOP_PHY:
		ret = 0;
		break;
	case MAC_INTERNALLOOP_SERDES:
		ret = dsaf_dev->misc_op->cfg_serdes_loopback(vf_cb->mac_cb,
							     !!en);
		break;
	case MAC_INTERNALLOOP_MAC:
		ret = hns_mac_config_mac_loopback(vf_cb->mac_cb, loop, en);
		break;
	default:
		ret = -EINVAL;
	}

	return ret;
}