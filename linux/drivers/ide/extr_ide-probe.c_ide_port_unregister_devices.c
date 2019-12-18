#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ present; } ;
typedef  TYPE_1__ ide_hwif_t ;

/* Variables and functions */
 int /*<<< orphan*/  __ide_port_unregister_devices (TYPE_1__*) ; 
 int /*<<< orphan*/  ide_cfg_mtx ; 
 int /*<<< orphan*/  ide_port_init_devices_data (TYPE_1__*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void ide_port_unregister_devices(ide_hwif_t *hwif)
{
	mutex_lock(&ide_cfg_mtx);
	__ide_port_unregister_devices(hwif);
	hwif->present = 0;
	ide_port_init_devices_data(hwif);
	mutex_unlock(&ide_cfg_mtx);
}