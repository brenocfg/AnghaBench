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
struct platform_device {int dummy; } ;
struct gpiomtd {scalar_t__ nce; scalar_t__ nwp; int /*<<< orphan*/  nand_chip; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (scalar_t__) ; 
 int /*<<< orphan*/  gpiod_set_value (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nand_release (int /*<<< orphan*/ *) ; 
 struct gpiomtd* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int gpio_nand_remove(struct platform_device *pdev)
{
	struct gpiomtd *gpiomtd = platform_get_drvdata(pdev);

	nand_release(&gpiomtd->nand_chip);

	/* Enable write protection and disable the chip */
	if (gpiomtd->nwp && !IS_ERR(gpiomtd->nwp))
		gpiod_set_value(gpiomtd->nwp, 0);
	if (gpiomtd->nce && !IS_ERR(gpiomtd->nce))
		gpiod_set_value(gpiomtd->nce, 0);

	return 0;
}