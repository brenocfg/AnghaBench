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
struct TYPE_5__ {int /*<<< orphan*/  index; } ;
typedef  TYPE_1__ ide_hwif_t ;

/* Variables and functions */
 int /*<<< orphan*/  ide_free_port_slot (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ide_port_free_devices (TYPE_1__*) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 

__attribute__((used)) static void ide_port_free(ide_hwif_t *hwif)
{
	ide_port_free_devices(hwif);
	ide_free_port_slot(hwif->index);
	kfree(hwif);
}