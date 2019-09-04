#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  dvb_gpio; int /*<<< orphan*/  suspend_gpio; } ;
struct em28xx {int mode; int /*<<< orphan*/  ctl_input; TYPE_1__ board; } ;
typedef  enum em28xx_mode { ____Placeholder_em28xx_mode } em28xx_mode ;
struct TYPE_4__ {int /*<<< orphan*/  gpio; } ;

/* Variables and functions */
 scalar_t__ EM28XX_DIGITAL_MODE ; 
 int EM28XX_SUSPEND ; 
 TYPE_2__* INPUT (int /*<<< orphan*/ ) ; 
 int em28xx_gpio_set (struct em28xx*,int /*<<< orphan*/ ) ; 

int em28xx_set_mode(struct em28xx *dev, enum em28xx_mode set_mode)
{
	if (dev->mode == set_mode)
		return 0;

	if (set_mode == EM28XX_SUSPEND) {
		dev->mode = set_mode;

		/* FIXME: add suspend support for ac97 */

		return em28xx_gpio_set(dev, dev->board.suspend_gpio);
	}

	dev->mode = set_mode;

	if (dev->mode == EM28XX_DIGITAL_MODE)
		return em28xx_gpio_set(dev, dev->board.dvb_gpio);
	else
		return em28xx_gpio_set(dev, INPUT(dev->ctl_input)->gpio);
}