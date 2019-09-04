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
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 
 struct tpm_chip* tpm_default_chip () ; 
 int tpm_try_get_ops (struct tpm_chip*) ; 

struct tpm_chip *tpm_find_get_ops(struct tpm_chip *chip)
{
	int rc;

	if (chip) {
		if (!tpm_try_get_ops(chip))
			return chip;
		return NULL;
	}

	chip = tpm_default_chip();
	if (!chip)
		return NULL;
	rc = tpm_try_get_ops(chip);
	/* release additional reference we got from tpm_default_chip() */
	put_device(&chip->dev);
	if (rc)
		return NULL;
	return chip;
}