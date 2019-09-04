#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  devt; } ;
struct tpm_chip {int flags; int /*<<< orphan*/  dev_num; TYPE_1__ devs; int /*<<< orphan*/  cdevs; TYPE_1__ dev; int /*<<< orphan*/  cdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAJOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MINOR (int /*<<< orphan*/ ) ; 
 int TPM_CHIP_FLAG_TPM2 ; 
 int cdev_device_add (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_name (TYPE_1__*) ; 
 int /*<<< orphan*/  dev_nums_idr ; 
 int /*<<< orphan*/  idr_lock ; 
 int /*<<< orphan*/  idr_replace (int /*<<< orphan*/ *,struct tpm_chip*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tpm_add_char_device(struct tpm_chip *chip)
{
	int rc;

	rc = cdev_device_add(&chip->cdev, &chip->dev);
	if (rc) {
		dev_err(&chip->dev,
			"unable to cdev_device_add() %s, major %d, minor %d, err=%d\n",
			dev_name(&chip->dev), MAJOR(chip->dev.devt),
			MINOR(chip->dev.devt), rc);
		return rc;
	}

	if (chip->flags & TPM_CHIP_FLAG_TPM2) {
		rc = cdev_device_add(&chip->cdevs, &chip->devs);
		if (rc) {
			dev_err(&chip->devs,
				"unable to cdev_device_add() %s, major %d, minor %d, err=%d\n",
				dev_name(&chip->devs), MAJOR(chip->devs.devt),
				MINOR(chip->devs.devt), rc);
			return rc;
		}
	}

	/* Make the chip available. */
	mutex_lock(&idr_lock);
	idr_replace(&dev_nums_idr, chip, chip->dev_num);
	mutex_unlock(&idr_lock);

	return rc;
}