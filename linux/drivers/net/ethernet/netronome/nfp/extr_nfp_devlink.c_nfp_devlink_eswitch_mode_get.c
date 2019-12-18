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
struct nfp_pf {int /*<<< orphan*/  app; } ;
struct devlink {int dummy; } ;

/* Variables and functions */
 struct nfp_pf* devlink_priv (struct devlink*) ; 
 int nfp_app_eswitch_mode_get (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nfp_devlink_eswitch_mode_get(struct devlink *devlink, u16 *mode)
{
	struct nfp_pf *pf = devlink_priv(devlink);

	return nfp_app_eswitch_mode_get(pf->app, mode);
}