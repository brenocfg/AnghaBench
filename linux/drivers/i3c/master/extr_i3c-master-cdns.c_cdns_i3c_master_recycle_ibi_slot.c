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
struct i3c_ibi_slot {int dummy; } ;
struct i3c_dev_desc {int dummy; } ;
struct cdns_i3c_i2c_dev_data {int /*<<< orphan*/  ibi_pool; } ;

/* Variables and functions */
 struct cdns_i3c_i2c_dev_data* i3c_dev_get_master_data (struct i3c_dev_desc*) ; 
 int /*<<< orphan*/  i3c_generic_ibi_recycle_slot (int /*<<< orphan*/ ,struct i3c_ibi_slot*) ; 

__attribute__((used)) static void cdns_i3c_master_recycle_ibi_slot(struct i3c_dev_desc *dev,
					     struct i3c_ibi_slot *slot)
{
	struct cdns_i3c_i2c_dev_data *data = i3c_dev_get_master_data(dev);

	i3c_generic_ibi_recycle_slot(data->ibi_pool, slot);
}