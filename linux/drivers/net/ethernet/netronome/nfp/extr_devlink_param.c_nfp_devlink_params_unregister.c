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

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devlink_params_unregister (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfp_devlink_params ; 
 int nfp_devlink_supports_params (struct nfp_pf*) ; 
 int /*<<< orphan*/  priv_to_devlink (struct nfp_pf*) ; 

void nfp_devlink_params_unregister(struct nfp_pf *pf)
{
	int err;

	err = nfp_devlink_supports_params(pf);
	if (err <= 0)
		return;

	devlink_params_unregister(priv_to_devlink(pf), nfp_devlink_params,
				  ARRAY_SIZE(nfp_devlink_params));
}