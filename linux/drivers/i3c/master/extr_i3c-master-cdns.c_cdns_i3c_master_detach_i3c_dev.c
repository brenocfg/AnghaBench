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
struct i3c_dev_desc {int dummy; } ;
struct cdns_i3c_master {int /*<<< orphan*/  free_rr_slots; scalar_t__ regs; } ;
struct cdns_i3c_i2c_dev_data {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 scalar_t__ DEVS_CTRL ; 
 int DEVS_CTRL_DEV_CLR (int /*<<< orphan*/ ) ; 
 struct i3c_master_controller* i3c_dev_get_master (struct i3c_dev_desc*) ; 
 struct cdns_i3c_i2c_dev_data* i3c_dev_get_master_data (struct i3c_dev_desc*) ; 
 int /*<<< orphan*/  i3c_dev_set_master_data (struct i3c_dev_desc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct cdns_i3c_i2c_dev_data*) ; 
 int readl (scalar_t__) ; 
 struct cdns_i3c_master* to_cdns_i3c_master (struct i3c_master_controller*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void cdns_i3c_master_detach_i3c_dev(struct i3c_dev_desc *dev)
{
	struct i3c_master_controller *m = i3c_dev_get_master(dev);
	struct cdns_i3c_master *master = to_cdns_i3c_master(m);
	struct cdns_i3c_i2c_dev_data *data = i3c_dev_get_master_data(dev);

	writel(readl(master->regs + DEVS_CTRL) |
	       DEVS_CTRL_DEV_CLR(data->id),
	       master->regs + DEVS_CTRL);

	i3c_dev_set_master_data(dev, NULL);
	master->free_rr_slots |= BIT(data->id);
	kfree(data);
}