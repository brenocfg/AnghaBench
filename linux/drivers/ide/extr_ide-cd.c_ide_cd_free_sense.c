#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int sense_rq_armed; int /*<<< orphan*/ * sense_rq; } ;
typedef  TYPE_1__ ide_drive_t ;

/* Variables and functions */
 int /*<<< orphan*/  blk_mq_free_request (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ide_cd_free_sense(ide_drive_t *drive)
{
	if (!drive->sense_rq)
		return;

	blk_mq_free_request(drive->sense_rq);
	drive->sense_rq = NULL;
	drive->sense_rq_armed = false;
}