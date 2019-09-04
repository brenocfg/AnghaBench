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
struct sch311x_gpio_priv {TYPE_1__* blocks; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  chip; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  gpiochip_remove (int /*<<< orphan*/ *) ; 
 struct sch311x_gpio_priv* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int sch311x_gpio_remove(struct platform_device *pdev)
{
	struct sch311x_gpio_priv *priv = platform_get_drvdata(pdev);
	int i;

	for (i = 0; i < ARRAY_SIZE(priv->blocks); i++) {
		gpiochip_remove(&priv->blocks[i].chip);
		dev_info(&pdev->dev,
			 "SMSC SCH311x GPIO block %d unregistered.\n", i);
	}
	return 0;
}