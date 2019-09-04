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

/* Variables and functions */
 int /*<<< orphan*/  S3C2410_GPF (int) ; 
 int /*<<< orphan*/  S3C2410_GPH (int) ; 
 int /*<<< orphan*/  S3C2416_MISCCR_SEL_SUSPND ; 
 int /*<<< orphan*/  S3C_GPIO_PULL_NONE ; 
 int /*<<< orphan*/  S3C_GPIO_PULL_UP ; 
 int /*<<< orphan*/  S3C_GPIO_SFN (int) ; 
 int /*<<< orphan*/  s3c2410_modify_misccr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s3c_gpio_cfgpin (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s3c_gpio_setpull (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void smdk2416_hsudc_gpio_init(void)
{
	s3c_gpio_setpull(S3C2410_GPH(14), S3C_GPIO_PULL_UP);
	s3c_gpio_setpull(S3C2410_GPF(2), S3C_GPIO_PULL_NONE);
	s3c_gpio_cfgpin(S3C2410_GPH(14), S3C_GPIO_SFN(1));
	s3c2410_modify_misccr(S3C2416_MISCCR_SEL_SUSPND, 0);
}