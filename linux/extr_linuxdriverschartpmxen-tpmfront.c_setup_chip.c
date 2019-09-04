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
struct tpm_private {struct tpm_chip* chip; int /*<<< orphan*/  read_queue; } ;
struct tpm_chip {int /*<<< orphan*/  dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct tpm_chip*) ; 
 int PTR_ERR (struct tpm_chip*) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,struct tpm_private*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tpm_vtpm ; 
 struct tpm_chip* tpmm_chip_alloc (struct device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int setup_chip(struct device *dev, struct tpm_private *priv)
{
	struct tpm_chip *chip;

	chip = tpmm_chip_alloc(dev, &tpm_vtpm);
	if (IS_ERR(chip))
		return PTR_ERR(chip);

	init_waitqueue_head(&priv->read_queue);

	priv->chip = chip;
	dev_set_drvdata(&chip->dev, priv);

	return 0;
}