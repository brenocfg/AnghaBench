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
struct s3fwrn5_i2c_phy {int mode; int irq_skip; int /*<<< orphan*/  mutex; int /*<<< orphan*/  gpio_en; int /*<<< orphan*/  gpio_fw_wake; } ;
typedef  enum s3fwrn5_mode { ____Placeholder_s3fwrn5_mode } s3fwrn5_mode ;

/* Variables and functions */
 int S3FWRN5_EN_WAIT_TIME ; 
 int S3FWRN5_MODE_COLD ; 
 int S3FWRN5_MODE_FW ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void s3fwrn5_i2c_set_mode(void *phy_id, enum s3fwrn5_mode mode)
{
	struct s3fwrn5_i2c_phy *phy = phy_id;

	mutex_lock(&phy->mutex);

	if (phy->mode == mode)
		goto out;

	phy->mode = mode;

	gpio_set_value(phy->gpio_en, 1);
	gpio_set_value(phy->gpio_fw_wake, 0);
	if (mode == S3FWRN5_MODE_FW)
		gpio_set_value(phy->gpio_fw_wake, 1);

	if (mode != S3FWRN5_MODE_COLD) {
		msleep(S3FWRN5_EN_WAIT_TIME);
		gpio_set_value(phy->gpio_en, 0);
		msleep(S3FWRN5_EN_WAIT_TIME/2);
	}

	phy->irq_skip = true;

out:
	mutex_unlock(&phy->mutex);
}