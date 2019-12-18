#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct i3c_master_controller {int dummy; } ;
struct i3c_dev_desc {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/ ** slots; } ;
struct cdns_i3c_master {TYPE_1__ ibi; } ;
struct cdns_i3c_i2c_dev_data {size_t ibi; int /*<<< orphan*/  ibi_pool; } ;

/* Variables and functions */
 struct i3c_master_controller* i3c_dev_get_master (struct i3c_dev_desc*) ; 
 struct cdns_i3c_i2c_dev_data* i3c_dev_get_master_data (struct i3c_dev_desc*) ; 
 int /*<<< orphan*/  i3c_generic_ibi_free_pool (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct cdns_i3c_master* to_cdns_i3c_master (struct i3c_master_controller*) ; 

__attribute__((used)) static void cdns_i3c_master_free_ibi(struct i3c_dev_desc *dev)
{
	struct i3c_master_controller *m = i3c_dev_get_master(dev);
	struct cdns_i3c_master *master = to_cdns_i3c_master(m);
	struct cdns_i3c_i2c_dev_data *data = i3c_dev_get_master_data(dev);
	unsigned long flags;

	spin_lock_irqsave(&master->ibi.lock, flags);
	master->ibi.slots[data->ibi] = NULL;
	data->ibi = -1;
	spin_unlock_irqrestore(&master->ibi.lock, flags);

	i3c_generic_ibi_free_pool(data->ibi_pool);
}