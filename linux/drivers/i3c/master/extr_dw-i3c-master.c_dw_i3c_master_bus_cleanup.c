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
struct dw_i3c_master {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dw_i3c_master_disable (struct dw_i3c_master*) ; 
 struct dw_i3c_master* to_dw_i3c_master (struct i3c_master_controller*) ; 

__attribute__((used)) static void dw_i3c_master_bus_cleanup(struct i3c_master_controller *m)
{
	struct dw_i3c_master *master = to_dw_i3c_master(m);

	dw_i3c_master_disable(master);
}