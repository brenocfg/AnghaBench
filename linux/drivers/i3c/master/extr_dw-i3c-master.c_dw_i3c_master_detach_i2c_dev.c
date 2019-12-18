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
struct i3c_master_controller {int dummy; } ;
struct i2c_dev_desc {int dummy; } ;
struct dw_i3c_master {int /*<<< orphan*/  free_pos; scalar_t__* addrs; int /*<<< orphan*/  datstartaddr; scalar_t__ regs; } ;
struct dw_i3c_i2c_dev_data {size_t index; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (size_t) ; 
 scalar_t__ DEV_ADDR_TABLE_LOC (int /*<<< orphan*/ ,size_t) ; 
 struct i3c_master_controller* i2c_dev_get_master (struct i2c_dev_desc*) ; 
 struct dw_i3c_i2c_dev_data* i2c_dev_get_master_data (struct i2c_dev_desc*) ; 
 int /*<<< orphan*/  i2c_dev_set_master_data (struct i2c_dev_desc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct dw_i3c_i2c_dev_data*) ; 
 struct dw_i3c_master* to_dw_i3c_master (struct i3c_master_controller*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void dw_i3c_master_detach_i2c_dev(struct i2c_dev_desc *dev)
{
	struct dw_i3c_i2c_dev_data *data = i2c_dev_get_master_data(dev);
	struct i3c_master_controller *m = i2c_dev_get_master(dev);
	struct dw_i3c_master *master = to_dw_i3c_master(m);

	writel(0,
	       master->regs +
	       DEV_ADDR_TABLE_LOC(master->datstartaddr, data->index));

	i2c_dev_set_master_data(dev, NULL);
	master->addrs[data->index] = 0;
	master->free_pos |= BIT(data->index);
	kfree(data);
}