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
struct nfp_app {TYPE_1__* pf; } ;
struct TYPE_2__ {int num_vfs; int /*<<< orphan*/  cpp; scalar_t__ vfcfg_tbl2; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 scalar_t__ NFP_NET_VF_CFG_MB_CAP ; 
 int /*<<< orphan*/  nfp_warn (int /*<<< orphan*/ ,char*,...) ; 
 int readw (scalar_t__) ; 

__attribute__((used)) static int
nfp_net_sriov_check(struct nfp_app *app, int vf, u16 cap, const char *msg)
{
	u16 cap_vf;

	if (!app || !app->pf->vfcfg_tbl2)
		return -EOPNOTSUPP;

	cap_vf = readw(app->pf->vfcfg_tbl2 + NFP_NET_VF_CFG_MB_CAP);
	if ((cap_vf & cap) != cap) {
		nfp_warn(app->pf->cpp, "ndo_set_vf_%s not supported\n", msg);
		return -EOPNOTSUPP;
	}

	if (vf < 0 || vf >= app->pf->num_vfs) {
		nfp_warn(app->pf->cpp, "invalid VF id %d\n", vf);
		return -EINVAL;
	}

	return 0;
}