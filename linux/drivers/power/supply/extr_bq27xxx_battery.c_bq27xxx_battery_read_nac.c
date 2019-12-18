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
struct bq27xxx_device_info {int opts; } ;

/* Variables and functions */
 int BQ27000_FLAG_CI ; 
 int BQ27XXX_O_ZERO ; 
 int /*<<< orphan*/  BQ27XXX_REG_FLAGS ; 
 int /*<<< orphan*/  BQ27XXX_REG_NAC ; 
 int ENODATA ; 
 int bq27xxx_battery_read_charge (struct bq27xxx_device_info*,int /*<<< orphan*/ ) ; 
 int bq27xxx_read (struct bq27xxx_device_info*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline int bq27xxx_battery_read_nac(struct bq27xxx_device_info *di)
{
	int flags;

	if (di->opts & BQ27XXX_O_ZERO) {
		flags = bq27xxx_read(di, BQ27XXX_REG_FLAGS, true);
		if (flags >= 0 && (flags & BQ27000_FLAG_CI))
			return -ENODATA;
	}

	return bq27xxx_battery_read_charge(di, BQ27XXX_REG_NAC);
}