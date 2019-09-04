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

/* Variables and functions */
 int /*<<< orphan*/  S3C2410_GPL (int) ; 
 int /*<<< orphan*/  S3C_GPIO_SFN (int) ; 
 int /*<<< orphan*/  s3c_gpio_cfgrange_nopull (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

void s3c2416_setup_sdhci1_cfg_gpio(struct platform_device *dev, int width)
{
	s3c_gpio_cfgrange_nopull(S3C2410_GPL(0), width, S3C_GPIO_SFN(2));
	s3c_gpio_cfgrange_nopull(S3C2410_GPL(8), 2, S3C_GPIO_SFN(2));
}