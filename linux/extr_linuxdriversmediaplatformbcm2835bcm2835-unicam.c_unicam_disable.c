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
struct unicam_cfg {int dummy; } ;
struct unicam_device {int max_data_lanes; struct unicam_cfg cfg; } ;

/* Variables and functions */
 int /*<<< orphan*/  UNICAM_ANA ; 
 int /*<<< orphan*/  UNICAM_CPE ; 
 int /*<<< orphan*/  UNICAM_CPR ; 
 int /*<<< orphan*/  UNICAM_CTRL ; 
 int /*<<< orphan*/  UNICAM_DAT0 ; 
 int /*<<< orphan*/  UNICAM_DAT1 ; 
 int /*<<< orphan*/  UNICAM_DAT2 ; 
 int /*<<< orphan*/  UNICAM_DAT3 ; 
 int /*<<< orphan*/  UNICAM_DDL ; 
 int /*<<< orphan*/  UNICAM_SOE ; 
 int /*<<< orphan*/  clk_write (struct unicam_cfg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_write (struct unicam_cfg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_write_field (struct unicam_cfg*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void unicam_disable(struct unicam_device *dev)
{
	struct unicam_cfg *cfg = &dev->cfg;

	/* Analogue lane control disable */
	reg_write_field(cfg, UNICAM_ANA, 1, UNICAM_DDL);

	/* Stop the output engine */
	reg_write_field(cfg, UNICAM_CTRL, 1, UNICAM_SOE);

	/* Disable the data lanes. */
	reg_write(cfg, UNICAM_DAT0, 0);
	reg_write(cfg, UNICAM_DAT1, 0);

	if (dev->max_data_lanes > 2) {
		reg_write(cfg, UNICAM_DAT2, 0);
		reg_write(cfg, UNICAM_DAT3, 0);
	}

	/* Peripheral reset */
	reg_write_field(cfg, UNICAM_CTRL, 1, UNICAM_CPR);
	usleep_range(50, 100);
	reg_write_field(cfg, UNICAM_CTRL, 0, UNICAM_CPR);

	/* Disable peripheral */
	reg_write_field(cfg, UNICAM_CTRL, 0, UNICAM_CPE);

	/* Disable all lane clocks */
	clk_write(cfg, 0);
}