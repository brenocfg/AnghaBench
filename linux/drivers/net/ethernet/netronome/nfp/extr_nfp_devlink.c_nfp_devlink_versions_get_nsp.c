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
typedef  int /*<<< orphan*/  u8 ;
struct nfp_devlink_versions {int /*<<< orphan*/  key; int /*<<< orphan*/  id; } ;
struct devlink_info_req {int dummy; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (struct nfp_devlink_versions*) ; 
 int ENOENT ; 
 scalar_t__ IS_ERR (char const*) ; 
 int PTR_ERR (char const*) ; 
 int devlink_info_version_running_put (struct devlink_info_req*,int /*<<< orphan*/ ,char const*) ; 
 int devlink_info_version_stored_put (struct devlink_info_req*,int /*<<< orphan*/ ,char const*) ; 
 struct nfp_devlink_versions* nfp_devlink_versions_nsp ; 
 char* nfp_nsp_versions_get (int /*<<< orphan*/ ,int,int /*<<< orphan*/  const*,unsigned int) ; 

__attribute__((used)) static int
nfp_devlink_versions_get_nsp(struct devlink_info_req *req, bool flash,
			     const u8 *buf, unsigned int size)
{
	unsigned int i;
	int err;

	for (i = 0; i < ARRAY_SIZE(nfp_devlink_versions_nsp); i++) {
		const struct nfp_devlink_versions *info;
		const char *version;

		info = &nfp_devlink_versions_nsp[i];

		version = nfp_nsp_versions_get(info->id, flash, buf, size);
		if (IS_ERR(version)) {
			if (PTR_ERR(version) == -ENOENT)
				continue;
			else
				return PTR_ERR(version);
		}

		if (flash)
			err = devlink_info_version_stored_put(req, info->key,
							      version);
		else
			err = devlink_info_version_running_put(req, info->key,
							       version);
		if (err)
			return err;
	}

	return 0;
}