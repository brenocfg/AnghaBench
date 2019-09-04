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
struct fsi_master_acf {int /*<<< orphan*/  gpio_data; int /*<<< orphan*/  gpio_clk; int /*<<< orphan*/  dev; int /*<<< orphan*/  gpio_tra_bit; int /*<<< orphan*/  gpio_tra_dreg; int /*<<< orphan*/  gpio_tra_vreg; int /*<<< orphan*/  gpio_trans; int /*<<< orphan*/  gpio_dat_bit; int /*<<< orphan*/  gpio_dat_dreg; int /*<<< orphan*/  gpio_dat_vreg; int /*<<< orphan*/  gpio_clk_bit; int /*<<< orphan*/  gpio_clk_dreg; int /*<<< orphan*/  gpio_clk_vreg; int /*<<< orphan*/  gpio_enable; int /*<<< orphan*/  gpio_mux; } ;

/* Variables and functions */
 int aspeed_gpio_copro_grab_gpio (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aspeed_gpio_copro_release_gpio (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gpiod_direction_output (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int setup_gpios_for_copro(struct fsi_master_acf *master)
{

	int rc;

	/* This aren't under ColdFire control, just set them up appropriately */
	gpiod_direction_output(master->gpio_mux, 1);
	gpiod_direction_output(master->gpio_enable, 1);

	/* Those are under ColdFire control, let it configure them */
	rc = aspeed_gpio_copro_grab_gpio(master->gpio_clk, &master->gpio_clk_vreg,
					 &master->gpio_clk_dreg, &master->gpio_clk_bit);
	if (rc) {
		dev_err(master->dev, "failed to assign clock gpio to coprocessor\n");
		return rc;
	}
	rc = aspeed_gpio_copro_grab_gpio(master->gpio_data, &master->gpio_dat_vreg,
					 &master->gpio_dat_dreg, &master->gpio_dat_bit);
	if (rc) {
		dev_err(master->dev, "failed to assign data gpio to coprocessor\n");
		aspeed_gpio_copro_release_gpio(master->gpio_clk);
		return rc;
	}
	rc = aspeed_gpio_copro_grab_gpio(master->gpio_trans, &master->gpio_tra_vreg,
					 &master->gpio_tra_dreg, &master->gpio_tra_bit);
	if (rc) {
		dev_err(master->dev, "failed to assign trans gpio to coprocessor\n");
		aspeed_gpio_copro_release_gpio(master->gpio_clk);
		aspeed_gpio_copro_release_gpio(master->gpio_data);
		return rc;
	}
	return 0;
}