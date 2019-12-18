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
struct sc27xx_efuse {int /*<<< orphan*/  mutex; int /*<<< orphan*/  dev; int /*<<< orphan*/  hwlock; } ;

/* Variables and functions */
 int /*<<< orphan*/  SC27XX_EFUSE_HWLOCK_TIMEOUT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int hwspin_lock_timeout_raw (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sc27xx_efuse_lock(struct sc27xx_efuse *efuse)
{
	int ret;

	mutex_lock(&efuse->mutex);

	ret = hwspin_lock_timeout_raw(efuse->hwlock,
				      SC27XX_EFUSE_HWLOCK_TIMEOUT);
	if (ret) {
		dev_err(efuse->dev, "timeout to get the hwspinlock\n");
		mutex_unlock(&efuse->mutex);
		return ret;
	}

	return 0;
}