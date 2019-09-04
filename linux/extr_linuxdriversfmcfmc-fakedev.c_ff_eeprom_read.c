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
struct fmc_device {scalar_t__ eeprom; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ FF_EEPROM_SIZE ; 
 int /*<<< orphan*/  memcpy (void*,scalar_t__,size_t) ; 

__attribute__((used)) static int ff_eeprom_read(struct fmc_device *fmc, uint32_t offset,
		void *buf, size_t size)
{
	if (offset > FF_EEPROM_SIZE)
		return -EINVAL;
	if (offset + size > FF_EEPROM_SIZE)
		size = FF_EEPROM_SIZE - offset;
	memcpy(buf, fmc->eeprom + offset, size);
	return size;
}