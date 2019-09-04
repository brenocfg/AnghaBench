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
struct netxen_adapter {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int do_rom_fast_read (struct netxen_adapter*,int,int*) ; 
 scalar_t__ netxen_rom_lock (struct netxen_adapter*) ; 
 int /*<<< orphan*/  netxen_rom_unlock (struct netxen_adapter*) ; 

int netxen_rom_fast_read(struct netxen_adapter *adapter, int addr, int *valp)
{
	int ret;

	if (netxen_rom_lock(adapter) != 0)
		return -EIO;

	ret = do_rom_fast_read(adapter, addr, valp);
	netxen_rom_unlock(adapter);
	return ret;
}