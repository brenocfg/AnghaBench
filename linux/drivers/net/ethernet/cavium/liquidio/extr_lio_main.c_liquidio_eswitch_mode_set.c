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
typedef  int u16 ;
struct TYPE_2__ {int app_cap_flags; } ;
struct octeon_device {int eswitch_mode; TYPE_1__ fw_info; } ;
struct netlink_ext_ack {int dummy; } ;
struct lio_devlink_priv {struct octeon_device* oct; } ;
struct devlink {int dummy; } ;

/* Variables and functions */
#define  DEVLINK_ESWITCH_MODE_LEGACY 129 
#define  DEVLINK_ESWITCH_MODE_SWITCHDEV 128 
 int EINVAL ; 
 int LIQUIDIO_SWITCHDEV_CAP ; 
 struct lio_devlink_priv* devlink_priv (struct devlink*) ; 
 int lio_vf_rep_create (struct octeon_device*) ; 
 int /*<<< orphan*/  lio_vf_rep_destroy (struct octeon_device*) ; 

__attribute__((used)) static int
liquidio_eswitch_mode_set(struct devlink *devlink, u16 mode,
			  struct netlink_ext_ack *extack)
{
	struct lio_devlink_priv *priv;
	struct octeon_device *oct;
	int ret = 0;

	priv = devlink_priv(devlink);
	oct = priv->oct;

	if (!(oct->fw_info.app_cap_flags & LIQUIDIO_SWITCHDEV_CAP))
		return -EINVAL;

	if (oct->eswitch_mode == mode)
		return 0;

	switch (mode) {
	case DEVLINK_ESWITCH_MODE_SWITCHDEV:
		oct->eswitch_mode = mode;
		ret = lio_vf_rep_create(oct);
		break;

	case DEVLINK_ESWITCH_MODE_LEGACY:
		lio_vf_rep_destroy(oct);
		oct->eswitch_mode = mode;
		break;

	default:
		ret = -EINVAL;
	}

	return ret;
}