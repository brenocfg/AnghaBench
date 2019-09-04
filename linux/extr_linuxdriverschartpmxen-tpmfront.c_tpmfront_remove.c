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
struct xenbus_device {int /*<<< orphan*/  dev; } ;
struct tpm_private {int dummy; } ;
struct tpm_chip {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 void* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ring_free (struct tpm_private*) ; 
 int /*<<< orphan*/  tpm_chip_unregister (struct tpm_chip*) ; 

__attribute__((used)) static int tpmfront_remove(struct xenbus_device *dev)
{
	struct tpm_chip *chip = dev_get_drvdata(&dev->dev);
	struct tpm_private *priv = dev_get_drvdata(&chip->dev);
	tpm_chip_unregister(chip);
	ring_free(priv);
	dev_set_drvdata(&chip->dev, NULL);
	return 0;
}