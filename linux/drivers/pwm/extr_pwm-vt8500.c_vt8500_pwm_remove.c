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
struct vt8500_chip {int /*<<< orphan*/  chip; int /*<<< orphan*/  clk; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  clk_unprepare (int /*<<< orphan*/ ) ; 
 struct vt8500_chip* platform_get_drvdata (struct platform_device*) ; 
 int pwmchip_remove (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vt8500_pwm_remove(struct platform_device *pdev)
{
	struct vt8500_chip *chip;

	chip = platform_get_drvdata(pdev);
	if (chip == NULL)
		return -ENODEV;

	clk_unprepare(chip->clk);

	return pwmchip_remove(&chip->chip);
}