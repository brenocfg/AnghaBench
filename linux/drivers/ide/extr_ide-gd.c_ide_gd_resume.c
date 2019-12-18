#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* disk_ops; int /*<<< orphan*/  id; } ;
typedef  TYPE_2__ ide_drive_t ;
struct TYPE_5__ {int /*<<< orphan*/  (* get_capacity ) (TYPE_2__*) ;} ;

/* Variables and functions */
 scalar_t__ ata_id_hpa_enabled (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

__attribute__((used)) static void ide_gd_resume(ide_drive_t *drive)
{
	if (ata_id_hpa_enabled(drive->id))
		(void)drive->disk_ops->get_capacity(drive);
}