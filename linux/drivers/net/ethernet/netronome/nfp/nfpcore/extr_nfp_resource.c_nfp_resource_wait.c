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
struct nfp_resource {int dummy; } ;
struct nfp_cpp {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 int ERESTARTSYS ; 
 int ETIMEDOUT ; 
 unsigned int HZ ; 
 int /*<<< orphan*/  IS_ERR (struct nfp_resource*) ; 
 unsigned int NFP_MUTEX_WAIT_FIRST_WARN ; 
 unsigned int NFP_MUTEX_WAIT_NEXT_WARN ; 
 int PTR_ERR (struct nfp_resource*) ; 
 unsigned int jiffies ; 
 scalar_t__ msleep_interruptible (int) ; 
 int /*<<< orphan*/  nfp_err (struct nfp_cpp*,char*,char const*,...) ; 
 int /*<<< orphan*/  nfp_info (struct nfp_cpp*,char*,char const*) ; 
 struct nfp_resource* nfp_resource_acquire (struct nfp_cpp*,char const*) ; 
 int /*<<< orphan*/  nfp_resource_release (struct nfp_resource*) ; 
 scalar_t__ time_is_before_eq_jiffies (unsigned long) ; 

int nfp_resource_wait(struct nfp_cpp *cpp, const char *name, unsigned int secs)
{
	unsigned long warn_at = jiffies + NFP_MUTEX_WAIT_FIRST_WARN * HZ;
	unsigned long err_at = jiffies + secs * HZ;
	struct nfp_resource *res;

	while (true) {
		res = nfp_resource_acquire(cpp, name);
		if (!IS_ERR(res)) {
			nfp_resource_release(res);
			return 0;
		}

		if (PTR_ERR(res) != -ENOENT) {
			nfp_err(cpp, "error waiting for resource %s: %ld\n",
				name, PTR_ERR(res));
			return PTR_ERR(res);
		}
		if (time_is_before_eq_jiffies(err_at)) {
			nfp_err(cpp, "timeout waiting for resource %s\n", name);
			return -ETIMEDOUT;
		}
		if (time_is_before_eq_jiffies(warn_at)) {
			warn_at = jiffies + NFP_MUTEX_WAIT_NEXT_WARN * HZ;
			nfp_info(cpp, "waiting for NFP resource %s\n", name);
		}
		if (msleep_interruptible(10)) {
			nfp_err(cpp, "wait for resource %s interrupted\n",
				name);
			return -ERESTARTSYS;
		}
	}
}