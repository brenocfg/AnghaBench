#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct platform_device {int dummy; } ;
struct mt6323_leds {int /*<<< orphan*/  lock; TYPE_2__* hw; TYPE_1__** led; } ;
struct TYPE_4__ {int /*<<< orphan*/  regmap; } ;
struct TYPE_3__ {int /*<<< orphan*/  cdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT6323_RG_DRV_32K_CK_PDN ; 
 int /*<<< orphan*/  MT6323_RG_DRV_32K_CK_PDN_MASK ; 
 int /*<<< orphan*/  MT6323_TOP_CKPDN0 ; 
 int /*<<< orphan*/  mt6323_led_hw_off (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 struct mt6323_leds* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mt6323_led_remove(struct platform_device *pdev)
{
	struct mt6323_leds *leds = platform_get_drvdata(pdev);
	int i;

	/* Turn the LEDs off on driver removal. */
	for (i = 0 ; leds->led[i] ; i++)
		mt6323_led_hw_off(&leds->led[i]->cdev);

	regmap_update_bits(leds->hw->regmap, MT6323_TOP_CKPDN0,
			   MT6323_RG_DRV_32K_CK_PDN_MASK,
			   MT6323_RG_DRV_32K_CK_PDN);

	mutex_destroy(&leds->lock);

	return 0;
}