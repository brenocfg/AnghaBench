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
struct ts5500_priv {int dummy; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 struct ts5500_priv* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  ts5500_disable_irq (struct ts5500_priv*) ; 

__attribute__((used)) static int ts5500_dio_remove(struct platform_device *pdev)
{
	struct ts5500_priv *priv = platform_get_drvdata(pdev);

	ts5500_disable_irq(priv);

	return 0;
}