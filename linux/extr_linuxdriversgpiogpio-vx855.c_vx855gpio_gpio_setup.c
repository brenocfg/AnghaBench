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
struct gpio_chip {char* label; int can_sleep; int /*<<< orphan*/  names; int /*<<< orphan*/  ngpio; scalar_t__ base; int /*<<< orphan*/ * dbg_show; int /*<<< orphan*/  set_config; int /*<<< orphan*/  set; int /*<<< orphan*/  get; int /*<<< orphan*/  direction_output; int /*<<< orphan*/  direction_input; int /*<<< orphan*/  owner; } ;
struct vx855_gpio {struct gpio_chip gpio; } ;

/* Variables and functions */
 int /*<<< orphan*/  NR_VX855_GP ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  vx855gpio_direction_input ; 
 int /*<<< orphan*/  vx855gpio_direction_output ; 
 int /*<<< orphan*/  vx855gpio_get ; 
 int /*<<< orphan*/  vx855gpio_names ; 
 int /*<<< orphan*/  vx855gpio_set ; 
 int /*<<< orphan*/  vx855gpio_set_config ; 

__attribute__((used)) static void vx855gpio_gpio_setup(struct vx855_gpio *vg)
{
	struct gpio_chip *c = &vg->gpio;

	c->label = "VX855 South Bridge";
	c->owner = THIS_MODULE;
	c->direction_input = vx855gpio_direction_input;
	c->direction_output = vx855gpio_direction_output;
	c->get = vx855gpio_get;
	c->set = vx855gpio_set;
	c->set_config = vx855gpio_set_config,
	c->dbg_show = NULL;
	c->base = 0;
	c->ngpio = NR_VX855_GP;
	c->can_sleep = false;
	c->names = vx855gpio_names;
}