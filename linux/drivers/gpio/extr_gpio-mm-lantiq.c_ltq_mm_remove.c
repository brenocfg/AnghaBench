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
struct ltq_mm {int /*<<< orphan*/  mmchip; } ;

/* Variables and functions */
 int /*<<< orphan*/  of_mm_gpiochip_remove (int /*<<< orphan*/ *) ; 
 struct ltq_mm* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int ltq_mm_remove(struct platform_device *pdev)
{
	struct ltq_mm *chip = platform_get_drvdata(pdev);

	of_mm_gpiochip_remove(&chip->mmchip);

	return 0;
}