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
struct private_data {int /*<<< orphan*/  avs_intr_base; int /*<<< orphan*/  base; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  brcm_avs_driver ; 
 int cpufreq_unregister_driver (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 struct private_data* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int brcm_avs_cpufreq_remove(struct platform_device *pdev)
{
	struct private_data *priv;
	int ret;

	ret = cpufreq_unregister_driver(&brcm_avs_driver);
	if (ret)
		return ret;

	priv = platform_get_drvdata(pdev);
	iounmap(priv->base);
	iounmap(priv->avs_intr_base);

	return 0;
}