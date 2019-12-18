#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sx150x_pinctrl {TYPE_3__* data; int /*<<< orphan*/  regmap; } ;
struct TYPE_4__ {int /*<<< orphan*/  reg_clock; } ;
struct TYPE_5__ {TYPE_1__ x789; } ;
struct TYPE_6__ {TYPE_2__ pri; } ;

/* Variables and functions */
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int sx150x_gpio_oscio_set(struct sx150x_pinctrl *pctl,
				 int value)
{
	return regmap_write(pctl->regmap,
			    pctl->data->pri.x789.reg_clock,
			    (value ? 0x1f : 0x10));
}