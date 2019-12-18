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
typedef  int u32 ;
struct zd_chip {int /*<<< orphan*/  mutex; int /*<<< orphan*/  rf; int /*<<< orphan*/  patch_cck_gain; } ;

/* Variables and functions */
 int /*<<< orphan*/  E2P_PHY_REG ; 
 int /*<<< orphan*/  ZD_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZD_CR47 ; 
 int /*<<< orphan*/  dev_dbg_f (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  mutex_is_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zd_chip_dev (struct zd_chip*) ; 
 int zd_ioread32_locked (struct zd_chip*,int*,int /*<<< orphan*/ ) ; 
 int zd_iowrite16_locked (struct zd_chip*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zd_rf_should_patch_cck_gain (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int patch_cck_gain(struct zd_chip *chip)
{
	int r;
	u32 value;

	if (!chip->patch_cck_gain || !zd_rf_should_patch_cck_gain(&chip->rf))
		return 0;

	ZD_ASSERT(mutex_is_locked(&chip->mutex));
	r = zd_ioread32_locked(chip, &value, E2P_PHY_REG);
	if (r)
		return r;
	dev_dbg_f(zd_chip_dev(chip), "patching value %x\n", value & 0xff);
	return zd_iowrite16_locked(chip, value & 0xff, ZD_CR47);
}