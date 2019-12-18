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
struct nfp_pf {int dummy; } ;
struct devlink {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devlink_params_publish (struct devlink*) ; 
 int devlink_params_register (struct devlink*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfp_devlink_params ; 
 int nfp_devlink_supports_params (struct nfp_pf*) ; 
 struct devlink* priv_to_devlink (struct nfp_pf*) ; 

int nfp_devlink_params_register(struct nfp_pf *pf)
{
	struct devlink *devlink = priv_to_devlink(pf);
	int err;

	err = nfp_devlink_supports_params(pf);
	if (err <= 0)
		return err;

	err = devlink_params_register(devlink, nfp_devlink_params,
				      ARRAY_SIZE(nfp_devlink_params));
	if (err)
		return err;

	devlink_params_publish(devlink);
	return 0;
}