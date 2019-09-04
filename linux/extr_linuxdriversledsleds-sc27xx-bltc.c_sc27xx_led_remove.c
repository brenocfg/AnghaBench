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
struct sc27xx_led_priv {int /*<<< orphan*/  lock; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 struct sc27xx_led_priv* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int sc27xx_led_remove(struct platform_device *pdev)
{
	struct sc27xx_led_priv *priv = platform_get_drvdata(pdev);

	mutex_destroy(&priv->lock);
	return 0;
}