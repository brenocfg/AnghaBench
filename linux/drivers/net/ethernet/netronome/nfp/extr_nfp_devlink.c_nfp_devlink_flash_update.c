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
struct netlink_ext_ack {int dummy; } ;
struct devlink {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  devlink_priv (struct devlink*) ; 
 int nfp_flash_update_common (int /*<<< orphan*/ ,char const*,struct netlink_ext_ack*) ; 

__attribute__((used)) static int
nfp_devlink_flash_update(struct devlink *devlink, const char *path,
			 const char *component, struct netlink_ext_ack *extack)
{
	if (component)
		return -EOPNOTSUPP;
	return nfp_flash_update_common(devlink_priv(devlink), path, extack);
}