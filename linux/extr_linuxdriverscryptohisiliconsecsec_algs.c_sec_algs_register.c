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

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int active_devs ; 
 int /*<<< orphan*/  algs_lock ; 
 int crypto_register_skciphers (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sec_algs ; 

int sec_algs_register(void)
{
	int ret = 0;

	mutex_lock(&algs_lock);
	if (++active_devs != 1)
		goto unlock;

	ret = crypto_register_skciphers(sec_algs, ARRAY_SIZE(sec_algs));
	if (ret)
		--active_devs;
unlock:
	mutex_unlock(&algs_lock);

	return ret;
}