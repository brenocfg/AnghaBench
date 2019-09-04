#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tpm_chip {int /*<<< orphan*/  dev; } ;
struct tpm_atmel_priv {int /*<<< orphan*/  iobase; int /*<<< orphan*/  region_size; int /*<<< orphan*/  base; scalar_t__ have_region; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  atmel_put_base_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atmel_release_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 TYPE_1__* pdev ; 
 int /*<<< orphan*/  platform_device_unregister (TYPE_1__*) ; 
 int /*<<< orphan*/  tpm_chip_unregister (struct tpm_chip*) ; 

__attribute__((used)) static void atml_plat_remove(void)
{
	struct tpm_chip *chip = dev_get_drvdata(&pdev->dev);
	struct tpm_atmel_priv *priv = dev_get_drvdata(&chip->dev);

	tpm_chip_unregister(chip);
	if (priv->have_region)
		atmel_release_region(priv->base, priv->region_size);
	atmel_put_base_addr(priv->iobase);
	platform_device_unregister(pdev);
}