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
typedef  int u32 ;
typedef  int u16 ;
struct wm97xx {int /*<<< orphan*/  codec_mutex; } ;
typedef  enum wm97xx_gpio_status { ____Placeholder_wm97xx_gpio_status } wm97xx_gpio_status ;

/* Variables and functions */
 int /*<<< orphan*/  AC97_GPIO_STATUS ; 
 int WM97XX_GPIO_HIGH ; 
 int WM97XX_GPIO_LOW ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int wm97xx_reg_read (struct wm97xx*,int /*<<< orphan*/ ) ; 

enum wm97xx_gpio_status wm97xx_get_gpio(struct wm97xx *wm, u32 gpio)
{
	u16 status;
	enum wm97xx_gpio_status ret;

	mutex_lock(&wm->codec_mutex);
	status = wm97xx_reg_read(wm, AC97_GPIO_STATUS);

	if (status & gpio)
		ret = WM97XX_GPIO_HIGH;
	else
		ret = WM97XX_GPIO_LOW;

	mutex_unlock(&wm->codec_mutex);
	return ret;
}