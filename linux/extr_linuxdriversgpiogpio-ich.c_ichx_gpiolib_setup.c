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
struct gpio_chip {int can_sleep; int /*<<< orphan*/ * dbg_show; int /*<<< orphan*/  ngpio; int /*<<< orphan*/  base; int /*<<< orphan*/  direction_output; int /*<<< orphan*/  direction_input; int /*<<< orphan*/  get_direction; int /*<<< orphan*/  set; scalar_t__ get; scalar_t__ request; int /*<<< orphan*/ * parent; int /*<<< orphan*/  label; int /*<<< orphan*/  owner; } ;
struct TYPE_6__ {TYPE_2__* desc; TYPE_1__* dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  ngpio; scalar_t__ get; scalar_t__ request; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRV_NAME ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  ichx_gpio_direction_input ; 
 int /*<<< orphan*/  ichx_gpio_direction_output ; 
 scalar_t__ ichx_gpio_get ; 
 int /*<<< orphan*/  ichx_gpio_get_direction ; 
 scalar_t__ ichx_gpio_request ; 
 int /*<<< orphan*/  ichx_gpio_set ; 
 TYPE_3__ ichx_priv ; 
 int /*<<< orphan*/  modparam_gpiobase ; 

__attribute__((used)) static void ichx_gpiolib_setup(struct gpio_chip *chip)
{
	chip->owner = THIS_MODULE;
	chip->label = DRV_NAME;
	chip->parent = &ichx_priv.dev->dev;

	/* Allow chip-specific overrides of request()/get() */
	chip->request = ichx_priv.desc->request ?
		ichx_priv.desc->request : ichx_gpio_request;
	chip->get = ichx_priv.desc->get ?
		ichx_priv.desc->get : ichx_gpio_get;

	chip->set = ichx_gpio_set;
	chip->get_direction = ichx_gpio_get_direction;
	chip->direction_input = ichx_gpio_direction_input;
	chip->direction_output = ichx_gpio_direction_output;
	chip->base = modparam_gpiobase;
	chip->ngpio = ichx_priv.desc->ngpio;
	chip->can_sleep = false;
	chip->dbg_show = NULL;
}