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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct mac_info {int /*<<< orphan*/  duplex; int /*<<< orphan*/  speed; int /*<<< orphan*/  auto_neg; } ;
struct mac_driver {int /*<<< orphan*/  (* get_info ) (struct mac_driver*,struct mac_info*) ;} ;
struct hns_mac_cb {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 struct mac_driver* hns_mac_get_drv (struct hns_mac_cb*) ; 
 int /*<<< orphan*/  stub1 (struct mac_driver*,struct mac_info*) ; 

int hns_mac_get_port_info(struct hns_mac_cb *mac_cb,
			  u8 *auto_neg, u16 *speed, u8 *duplex)
{
	struct mac_driver *mac_ctrl_drv;
	struct mac_info    info;

	mac_ctrl_drv = hns_mac_get_drv(mac_cb);

	if (!mac_ctrl_drv->get_info)
		return -ENODEV;

	mac_ctrl_drv->get_info(mac_ctrl_drv, &info);
	if (auto_neg)
		*auto_neg = info.auto_neg;
	if (speed)
		*speed = info.speed;
	if (duplex)
		*duplex = info.duplex;

	return 0;
}