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
struct tpm_chip {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_nums_idr ; 
 int /*<<< orphan*/  get_device (int /*<<< orphan*/ *) ; 
 struct tpm_chip* idr_get_next (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  idr_lock ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

struct tpm_chip *tpm_default_chip(void)
{
	struct tpm_chip *chip, *res = NULL;
	int chip_num = 0;
	int chip_prev;

	mutex_lock(&idr_lock);

	do {
		chip_prev = chip_num;
		chip = idr_get_next(&dev_nums_idr, &chip_num);
		if (chip) {
			get_device(&chip->dev);
			res = chip;
			break;
		}
	} while (chip_prev != chip_num);

	mutex_unlock(&idr_lock);

	return res;
}