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
struct nfp_cpp_mutex {int /*<<< orphan*/  cpp; int /*<<< orphan*/  key; int /*<<< orphan*/  address; int /*<<< orphan*/  target; int /*<<< orphan*/  depth; } ;

/* Variables and functions */
 int EBUSY ; 
 int ERESTARTSYS ; 
 unsigned long HZ ; 
 unsigned long NFP_MUTEX_WAIT_ERROR ; 
 unsigned long NFP_MUTEX_WAIT_FIRST_WARN ; 
 unsigned long NFP_MUTEX_WAIT_NEXT_WARN ; 
 unsigned long jiffies ; 
 int msleep_interruptible (unsigned int) ; 
 int nfp_cpp_mutex_trylock (struct nfp_cpp_mutex*) ; 
 int /*<<< orphan*/  nfp_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  nfp_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  nfp_warn (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ time_is_before_eq_jiffies (unsigned long) ; 

int nfp_cpp_mutex_lock(struct nfp_cpp_mutex *mutex)
{
	unsigned long warn_at = jiffies + NFP_MUTEX_WAIT_FIRST_WARN * HZ;
	unsigned long err_at = jiffies + NFP_MUTEX_WAIT_ERROR * HZ;
	unsigned int timeout_ms = 1;
	int err;

	/* We can't use a waitqueue here, because the unlocker
	 * might be on a separate CPU.
	 *
	 * So just wait for now.
	 */
	for (;;) {
		err = nfp_cpp_mutex_trylock(mutex);
		if (err != -EBUSY)
			break;

		err = msleep_interruptible(timeout_ms);
		if (err != 0) {
			nfp_info(mutex->cpp,
				 "interrupted waiting for NFP mutex\n");
			return -ERESTARTSYS;
		}

		if (time_is_before_eq_jiffies(warn_at)) {
			warn_at = jiffies + NFP_MUTEX_WAIT_NEXT_WARN * HZ;
			nfp_warn(mutex->cpp,
				 "Warning: waiting for NFP mutex [depth:%hd target:%d addr:%llx key:%08x]\n",
				 mutex->depth,
				 mutex->target, mutex->address, mutex->key);
		}
		if (time_is_before_eq_jiffies(err_at)) {
			nfp_err(mutex->cpp, "Error: mutex wait timed out\n");
			return -EBUSY;
		}
	}

	return err;
}