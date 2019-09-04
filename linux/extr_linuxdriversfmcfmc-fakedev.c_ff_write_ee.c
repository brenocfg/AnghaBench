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
struct fmc_device {int flags; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int FMC_DEVICE_HAS_GOLDEN ; 
 int ff_eeprom_write (struct fmc_device*,int,void const*,int) ; 

__attribute__((used)) static int ff_write_ee(struct fmc_device *fmc, int pos,
			 const void *data, int len)
{
	if (!(fmc->flags & FMC_DEVICE_HAS_GOLDEN))
		return -EOPNOTSUPP;
	return ff_eeprom_write(fmc, pos, data, len);
}