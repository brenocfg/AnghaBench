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
struct resource {int /*<<< orphan*/  start; } ;
struct nmk_i2c_dev {int /*<<< orphan*/  clk; scalar_t__ virtbase; int /*<<< orphan*/  adap; } ;
struct amba_device {struct resource res; } ;

/* Variables and functions */
 scalar_t__ I2C_CR ; 
 int /*<<< orphan*/  I2C_CR_PE ; 
 struct nmk_i2c_dev* amba_get_drvdata (struct amba_device*) ; 
 int /*<<< orphan*/  clear_all_interrupts (struct nmk_i2c_dev*) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disable_all_interrupts (struct nmk_i2c_dev*) ; 
 int /*<<< orphan*/  flush_i2c_fifo (struct nmk_i2c_dev*) ; 
 int /*<<< orphan*/  i2c_clr_bit (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_del_adapter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 

__attribute__((used)) static int nmk_i2c_remove(struct amba_device *adev)
{
	struct resource *res = &adev->res;
	struct nmk_i2c_dev *dev = amba_get_drvdata(adev);

	i2c_del_adapter(&dev->adap);
	flush_i2c_fifo(dev);
	disable_all_interrupts(dev);
	clear_all_interrupts(dev);
	/* disable the controller */
	i2c_clr_bit(dev->virtbase + I2C_CR, I2C_CR_PE);
	clk_disable_unprepare(dev->clk);
	release_mem_region(res->start, resource_size(res));

	return 0;
}