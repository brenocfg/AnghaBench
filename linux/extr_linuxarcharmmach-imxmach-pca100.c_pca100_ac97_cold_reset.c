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
struct snd_ac97 {int dummy; } ;

/* Variables and functions */
 int GPIO_GPIO ; 
 int GPIO_OUT ; 
 int GPIO_PORTC ; 
 int PC20_PF_SSI1_FS ; 
 int PC22_PF_SSI1_TXD ; 
 int /*<<< orphan*/  gpio_set_value (int,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  mxc_gpio_mode (int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void pca100_ac97_cold_reset(struct snd_ac97 *ac97)
{
	mxc_gpio_mode(GPIO_PORTC | 20 | GPIO_GPIO | GPIO_OUT);  /* FS */
	gpio_set_value(GPIO_PORTC + 20, 0);
	mxc_gpio_mode(GPIO_PORTC | 22 | GPIO_GPIO | GPIO_OUT);  /* TX */
	gpio_set_value(GPIO_PORTC + 22, 0);
	mxc_gpio_mode(GPIO_PORTC | 28 | GPIO_GPIO | GPIO_OUT);  /* reset */
	gpio_set_value(GPIO_PORTC + 28, 0);
	udelay(10);
	gpio_set_value(GPIO_PORTC + 28, 1);
	mxc_gpio_mode(PC20_PF_SSI1_FS);
	mxc_gpio_mode(PC22_PF_SSI1_TXD);
	msleep(2);
}