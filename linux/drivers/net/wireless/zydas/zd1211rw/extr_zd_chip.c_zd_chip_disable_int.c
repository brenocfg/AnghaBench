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
struct zd_chip {int /*<<< orphan*/  mutex; int /*<<< orphan*/  usb; } ;
struct TYPE_2__ {int /*<<< orphan*/  process_intr; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__* zd_chip_to_mac (struct zd_chip*) ; 
 int /*<<< orphan*/  zd_usb_disable_int (int /*<<< orphan*/ *) ; 

void zd_chip_disable_int(struct zd_chip *chip)
{
	mutex_lock(&chip->mutex);
	zd_usb_disable_int(&chip->usb);
	mutex_unlock(&chip->mutex);

	/* cancel pending interrupt work */
	cancel_work_sync(&zd_chip_to_mac(chip)->process_intr);
}