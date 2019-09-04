#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * disks; } ;
typedef  TYPE_1__ DAC960_Controller_T ;

/* Variables and functions */
 int DAC960_MaxLogicalDrives ; 
 int /*<<< orphan*/  disk_size (TYPE_1__*,int) ; 
 int /*<<< orphan*/  set_capacity (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void DAC960_ComputeGenericDiskInfo(DAC960_Controller_T *Controller)
{
	int disk;
	for (disk = 0; disk < DAC960_MaxLogicalDrives; disk++)
		set_capacity(Controller->disks[disk], disk_size(Controller, disk));
}