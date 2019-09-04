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
struct samsung_gpio_chip {int dummy; } ;
typedef  int /*<<< orphan*/  samsung_gpio_pull_t ;

/* Variables and functions */
 int /*<<< orphan*/  S3C_GPIO_PULL_UP ; 
 int /*<<< orphan*/  s3c24xx_gpio_getpull_1 (struct samsung_gpio_chip*,unsigned int,int /*<<< orphan*/ ) ; 

samsung_gpio_pull_t s3c24xx_gpio_getpull_1up(struct samsung_gpio_chip *chip,
					     unsigned int off)
{
	return s3c24xx_gpio_getpull_1(chip, off, S3C_GPIO_PULL_UP);
}