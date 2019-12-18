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
typedef  int /*<<< orphan*/  u16 ;
struct nfp_pf {int /*<<< orphan*/  lock; int /*<<< orphan*/  app; } ;
struct netlink_ext_ack {int dummy; } ;
struct devlink {int dummy; } ;

/* Variables and functions */
 struct nfp_pf* devlink_priv (struct devlink*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int nfp_app_eswitch_mode_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nfp_devlink_eswitch_mode_set(struct devlink *devlink, u16 mode,
					struct netlink_ext_ack *extack)
{
	struct nfp_pf *pf = devlink_priv(devlink);
	int ret;

	mutex_lock(&pf->lock);
	ret = nfp_app_eswitch_mode_set(pf->app, mode);
	mutex_unlock(&pf->lock);

	return ret;
}