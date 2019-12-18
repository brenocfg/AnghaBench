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
struct sc27xx_efuse {int /*<<< orphan*/  mutex; int /*<<< orphan*/  hwlock; } ;

/* Variables and functions */
 int /*<<< orphan*/  hwspin_unlock_raw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sc27xx_efuse_unlock(struct sc27xx_efuse *efuse)
{
	hwspin_unlock_raw(efuse->hwlock);
	mutex_unlock(&efuse->mutex);
}