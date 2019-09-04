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
 int /*<<< orphan*/  S3C2410_GPE (int) ; 
 int /*<<< orphan*/  S3C2410_GPE14_IICSCL ; 
 int /*<<< orphan*/  S3C2410_GPE15_IICSDA ; 
 int /*<<< orphan*/  s3c_gpio_cfgpin (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void s3c_i2c0_cfg_gpio(struct platform_device *dev)
{
	s3c_gpio_cfgpin(S3C2410_GPE(15), S3C2410_GPE15_IICSDA);
	s3c_gpio_cfgpin(S3C2410_GPE(14), S3C2410_GPE14_IICSCL);
}