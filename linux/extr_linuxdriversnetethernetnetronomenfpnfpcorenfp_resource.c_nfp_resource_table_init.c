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
typedef  scalar_t__ u64 ;
struct nfp_resource_entry {int dummy; } ;
struct nfp_cpp_mutex {int dummy; } ;
struct nfp_cpp {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 scalar_t__ NFP_RESOURCE_TBL_BASE ; 
 int NFP_RESOURCE_TBL_ENTRIES ; 
 int /*<<< orphan*/  NFP_RESOURCE_TBL_KEY ; 
 int /*<<< orphan*/  NFP_RESOURCE_TBL_TARGET ; 
 struct nfp_cpp_mutex* nfp_cpp_mutex_alloc (struct nfp_cpp*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfp_cpp_mutex_free (struct nfp_cpp_mutex*) ; 
 scalar_t__ nfp_cpp_mutex_lock (struct nfp_cpp_mutex*) ; 
 int nfp_cpp_mutex_reclaim (struct nfp_cpp*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  nfp_cpp_mutex_unlock (struct nfp_cpp_mutex*) ; 
 int /*<<< orphan*/  nfp_err (struct nfp_cpp*,char*,...) ; 
 int /*<<< orphan*/  nfp_warn (struct nfp_cpp*,char*,...) ; 

int nfp_resource_table_init(struct nfp_cpp *cpp)
{
	struct nfp_cpp_mutex *dev_mutex;
	int i, err;

	err = nfp_cpp_mutex_reclaim(cpp, NFP_RESOURCE_TBL_TARGET,
				    NFP_RESOURCE_TBL_BASE);
	if (err < 0) {
		nfp_err(cpp, "Error: failed to reclaim resource table mutex\n");
		return err;
	}
	if (err)
		nfp_warn(cpp, "Warning: busted main resource table mutex\n");

	dev_mutex = nfp_cpp_mutex_alloc(cpp, NFP_RESOURCE_TBL_TARGET,
					NFP_RESOURCE_TBL_BASE,
					NFP_RESOURCE_TBL_KEY);
	if (!dev_mutex)
		return -ENOMEM;

	if (nfp_cpp_mutex_lock(dev_mutex)) {
		nfp_err(cpp, "Error: failed to claim resource table mutex\n");
		nfp_cpp_mutex_free(dev_mutex);
		return -EINVAL;
	}

	/* Resource 0 is the dev_mutex, start from 1 */
	for (i = 1; i < NFP_RESOURCE_TBL_ENTRIES; i++) {
		u64 addr = NFP_RESOURCE_TBL_BASE +
			sizeof(struct nfp_resource_entry) * i;

		err = nfp_cpp_mutex_reclaim(cpp, NFP_RESOURCE_TBL_TARGET, addr);
		if (err < 0) {
			nfp_err(cpp,
				"Error: failed to reclaim resource %d mutex\n",
				i);
			goto err_unlock;
		}
		if (err)
			nfp_warn(cpp, "Warning: busted resource %d mutex\n", i);
	}

	err = 0;
err_unlock:
	nfp_cpp_mutex_unlock(dev_mutex);
	nfp_cpp_mutex_free(dev_mutex);

	return err;
}