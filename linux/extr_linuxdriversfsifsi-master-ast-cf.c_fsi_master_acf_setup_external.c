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
struct fsi_master_acf {int /*<<< orphan*/  gpio_data; int /*<<< orphan*/  gpio_clk; int /*<<< orphan*/  gpio_enable; int /*<<< orphan*/  gpio_trans; int /*<<< orphan*/  gpio_mux; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpiod_direction_input (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiod_direction_output (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void fsi_master_acf_setup_external(struct fsi_master_acf *master)
{
	/* Setup GPIOs for external FSI master (FSP box) */
	gpiod_direction_output(master->gpio_mux, 0);
	gpiod_direction_output(master->gpio_trans, 0);
	gpiod_direction_output(master->gpio_enable, 1);
	gpiod_direction_input(master->gpio_clk);
	gpiod_direction_input(master->gpio_data);
}