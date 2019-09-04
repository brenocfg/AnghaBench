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
struct fsi_master_gpio {int /*<<< orphan*/  gpio_data; int /*<<< orphan*/  gpio_trans; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpiod_direction_output (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gpiod_set_value (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void set_sda_output(struct fsi_master_gpio *master, int value)
{
	gpiod_set_value(master->gpio_trans, 1);
	gpiod_direction_output(master->gpio_data, value);
}