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
typedef  int u32 ;
struct i3c_master_controller {int dummy; } ;
struct TYPE_2__ {scalar_t__ static_addr; scalar_t__ dyn_addr; } ;
struct i3c_dev_desc {TYPE_1__ info; } ;
struct cdns_i3c_master {scalar_t__ regs; } ;
struct cdns_i3c_i2c_dev_data {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 scalar_t__ DEV_ID_RR0 (int /*<<< orphan*/ ) ; 
 int DEV_ID_RR0_IS_I3C ; 
 struct i3c_master_controller* i3c_dev_get_master (struct i3c_dev_desc*) ; 
 struct cdns_i3c_i2c_dev_data* i3c_dev_get_master_data (struct i3c_dev_desc*) ; 
 int prepare_rr0_dev_address (scalar_t__) ; 
 struct cdns_i3c_master* to_cdns_i3c_master (struct i3c_master_controller*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void cdns_i3c_master_upd_i3c_addr(struct i3c_dev_desc *dev)
{
	struct i3c_master_controller *m = i3c_dev_get_master(dev);
	struct cdns_i3c_master *master = to_cdns_i3c_master(m);
	struct cdns_i3c_i2c_dev_data *data = i3c_dev_get_master_data(dev);
	u32 rr;

	rr = prepare_rr0_dev_address(dev->info.dyn_addr ?
				     dev->info.dyn_addr :
				     dev->info.static_addr);
	writel(DEV_ID_RR0_IS_I3C | rr, master->regs + DEV_ID_RR0(data->id));
}