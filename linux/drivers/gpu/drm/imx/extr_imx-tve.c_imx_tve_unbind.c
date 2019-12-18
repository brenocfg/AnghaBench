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
struct imx_tve {int /*<<< orphan*/  dac_reg; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 struct imx_tve* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void imx_tve_unbind(struct device *dev, struct device *master,
	void *data)
{
	struct imx_tve *tve = dev_get_drvdata(dev);

	if (!IS_ERR(tve->dac_reg))
		regulator_disable(tve->dac_reg);
}