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
struct nfp_resource {int /*<<< orphan*/  mutex; } ;
struct nfp_cpp_mutex {int dummy; } ;
struct nfp_cpp {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  nfp_cpp_mutex_free (int /*<<< orphan*/ ) ; 
 scalar_t__ nfp_cpp_mutex_lock (struct nfp_cpp_mutex*) ; 
 int nfp_cpp_mutex_trylock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfp_cpp_mutex_unlock (struct nfp_cpp_mutex*) ; 
 int nfp_cpp_resource_find (struct nfp_cpp*,struct nfp_resource*) ; 

__attribute__((used)) static int
nfp_resource_try_acquire(struct nfp_cpp *cpp, struct nfp_resource *res,
			 struct nfp_cpp_mutex *dev_mutex)
{
	int err;

	if (nfp_cpp_mutex_lock(dev_mutex))
		return -EINVAL;

	err = nfp_cpp_resource_find(cpp, res);
	if (err)
		goto err_unlock_dev;

	err = nfp_cpp_mutex_trylock(res->mutex);
	if (err)
		goto err_res_mutex_free;

	nfp_cpp_mutex_unlock(dev_mutex);

	return 0;

err_res_mutex_free:
	nfp_cpp_mutex_free(res->mutex);
err_unlock_dev:
	nfp_cpp_mutex_unlock(dev_mutex);

	return err;
}