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
typedef  scalar_t__ uint32_t ;
struct fmc_device {scalar_t__ eeprom; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ FF_EEPROM_SIZE ; 
 int HZ ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int,size_t) ; 
 int /*<<< orphan*/  ff_work ; 
 int /*<<< orphan*/  memcpy (scalar_t__,void const*,size_t) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int ff_eeprom_write(struct fmc_device *fmc, uint32_t offset,
		    const void *buf, size_t size)
{
	if (offset > FF_EEPROM_SIZE)
		return -EINVAL;
	if (offset + size > FF_EEPROM_SIZE)
		size = FF_EEPROM_SIZE - offset;
	dev_info(&fmc->dev, "write_eeprom: offset %i, size %zi\n",
		 (int)offset, size);
	memcpy(fmc->eeprom + offset, buf, size);
	schedule_delayed_work(&ff_work, HZ * 2); /* remove, replug, in 2s */
	return size;
}