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
struct vxgedev {struct __vxge_hw_device* devh; } ;
struct net_device {int dummy; } ;
struct __vxge_hw_device {int dummy; } ;
typedef  enum ethtool_phys_id_state { ____Placeholder_ethtool_phys_id_state } ethtool_phys_id_state ;

/* Variables and functions */
 int EINVAL ; 
#define  ETHTOOL_ID_ACTIVE 129 
#define  ETHTOOL_ID_INACTIVE 128 
 int /*<<< orphan*/  VXGE_FLICKER_OFF ; 
 int /*<<< orphan*/  VXGE_FLICKER_ON ; 
 struct vxgedev* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  vxge_hw_device_flick_link_led (struct __vxge_hw_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vxge_ethtool_idnic(struct net_device *dev,
			      enum ethtool_phys_id_state state)
{
	struct vxgedev *vdev = netdev_priv(dev);
	struct __vxge_hw_device *hldev = vdev->devh;

	switch (state) {
	case ETHTOOL_ID_ACTIVE:
		vxge_hw_device_flick_link_led(hldev, VXGE_FLICKER_ON);
		break;

	case ETHTOOL_ID_INACTIVE:
		vxge_hw_device_flick_link_led(hldev, VXGE_FLICKER_OFF);
		break;

	default:
		return -EINVAL;
	}

	return 0;
}