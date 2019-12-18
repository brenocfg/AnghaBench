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
typedef  scalar_t__ u8 ;
typedef  int u16 ;
struct wusbhc {scalar_t__ ports_max; int /*<<< orphan*/  mutex; struct device* dev; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOSYS ; 
 int EPIPE ; 
#define  USB_PORT_FEAT_C_CONNECTION 136 
#define  USB_PORT_FEAT_C_ENABLE 135 
#define  USB_PORT_FEAT_C_OVER_CURRENT 134 
#define  USB_PORT_FEAT_C_RESET 133 
#define  USB_PORT_FEAT_C_SUSPEND 132 
#define  USB_PORT_FEAT_ENABLE 131 
#define  USB_PORT_FEAT_POWER 130 
#define  USB_PORT_FEAT_RESET 129 
#define  USB_PORT_FEAT_SUSPEND 128 
 int /*<<< orphan*/  USB_PORT_STAT_POWER ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,scalar_t__,int,scalar_t__) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__* wusb_port_by_idx (struct wusbhc*,scalar_t__) ; 
 int wusbhc_rh_port_reset (struct wusbhc*,scalar_t__) ; 

__attribute__((used)) static int wusbhc_rh_set_port_feat(struct wusbhc *wusbhc, u16 feature,
				   u8 selector, u8 port_idx)
{
	struct device *dev = wusbhc->dev;

	if (port_idx > wusbhc->ports_max)
		return -EINVAL;

	switch (feature) {
		/* According to USB2.0[11.24.2.13]p2, these features
		 * are not required to be implemented. */
	case USB_PORT_FEAT_C_OVER_CURRENT:
	case USB_PORT_FEAT_C_ENABLE:
	case USB_PORT_FEAT_C_SUSPEND:
	case USB_PORT_FEAT_C_CONNECTION:
	case USB_PORT_FEAT_C_RESET:
		return 0;
	case USB_PORT_FEAT_POWER:
		/* No such thing, but we fake it works */
		mutex_lock(&wusbhc->mutex);
		wusb_port_by_idx(wusbhc, port_idx)->status |= USB_PORT_STAT_POWER;
		mutex_unlock(&wusbhc->mutex);
		return 0;
	case USB_PORT_FEAT_RESET:
		return wusbhc_rh_port_reset(wusbhc, port_idx);
	case USB_PORT_FEAT_ENABLE:
	case USB_PORT_FEAT_SUSPEND:
		dev_err(dev, "(port_idx %d) set feat %d/%d UNIMPLEMENTED\n",
			port_idx, feature, selector);
		return -ENOSYS;
	default:
		dev_err(dev, "(port_idx %d) set feat %d/%d UNKNOWN\n",
			port_idx, feature, selector);
		return -EPIPE;
	}

	return 0;
}