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
typedef  int /*<<< orphan*/  u8 ;
struct qib_devdata {int /*<<< orphan*/  eep_lock; } ;

/* Variables and functions */
 int eeprom_write_with_enable (struct qib_devdata*,int /*<<< orphan*/ ,void const*,int) ; 
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int qib_eeprom_write(struct qib_devdata *dd, u8 eeprom_offset,
		     const void *buff, int len)
{
	int ret;

	ret = mutex_lock_interruptible(&dd->eep_lock);
	if (!ret) {
		ret = eeprom_write_with_enable(dd, eeprom_offset, buff, len);
		mutex_unlock(&dd->eep_lock);
	}

	return ret;
}