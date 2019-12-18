#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct regulator_dev {int dummy; } ;
struct isl_pmic {int /*<<< orphan*/  mtx; TYPE_1__* client; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int i2c_smbus_write_byte (TYPE_1__*,unsigned int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct isl_pmic* rdev_get_drvdata (struct regulator_dev*) ; 

__attribute__((used)) static int isl6271a_set_voltage_sel(struct regulator_dev *dev,
				    unsigned selector)
{
	struct isl_pmic *pmic = rdev_get_drvdata(dev);
	int err;

	mutex_lock(&pmic->mtx);

	err = i2c_smbus_write_byte(pmic->client, selector);
	if (err < 0)
		dev_err(&pmic->client->dev, "Error setting voltage\n");

	mutex_unlock(&pmic->mtx);
	return err;
}