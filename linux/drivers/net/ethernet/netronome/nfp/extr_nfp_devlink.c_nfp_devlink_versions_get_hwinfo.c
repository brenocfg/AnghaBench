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
struct nfp_pf {int /*<<< orphan*/  hwinfo; } ;
struct nfp_devlink_versions_simple {int /*<<< orphan*/  key; int /*<<< orphan*/  hwinfo; } ;
struct devlink_info_req {int dummy; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (struct nfp_devlink_versions_simple*) ; 
 int devlink_info_version_fixed_put (struct devlink_info_req*,int /*<<< orphan*/ ,char const*) ; 
 struct nfp_devlink_versions_simple* nfp_devlink_versions_hwinfo ; 
 char* nfp_hwinfo_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nfp_devlink_versions_get_hwinfo(struct nfp_pf *pf, struct devlink_info_req *req)
{
	unsigned int i;
	int err;

	for (i = 0; i < ARRAY_SIZE(nfp_devlink_versions_hwinfo); i++) {
		const struct nfp_devlink_versions_simple *info;
		const char *val;

		info = &nfp_devlink_versions_hwinfo[i];

		val = nfp_hwinfo_lookup(pf->hwinfo, info->hwinfo);
		if (!val)
			continue;

		err = devlink_info_version_fixed_put(req, info->key, val);
		if (err)
			return err;
	}

	return 0;
}