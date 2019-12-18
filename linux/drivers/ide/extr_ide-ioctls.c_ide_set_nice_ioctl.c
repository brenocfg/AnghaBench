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
struct TYPE_3__ {scalar_t__ media; int /*<<< orphan*/  dev_flags; } ;
typedef  TYPE_1__ ide_drive_t ;

/* Variables and functions */
 int EPERM ; 
 int /*<<< orphan*/  IDE_DFLAG_DSC_OVERLAP ; 
 int /*<<< orphan*/  IDE_DFLAG_NICE1 ; 
 int IDE_NICE_1 ; 
 int IDE_NICE_DSC_OVERLAP ; 
 scalar_t__ ide_tape ; 

__attribute__((used)) static int ide_set_nice_ioctl(ide_drive_t *drive, unsigned long arg)
{
	if (arg != (arg & ((1 << IDE_NICE_DSC_OVERLAP) | (1 << IDE_NICE_1))))
		return -EPERM;

	if (((arg >> IDE_NICE_DSC_OVERLAP) & 1) &&
	    (drive->media != ide_tape))
		return -EPERM;

	if ((arg >> IDE_NICE_DSC_OVERLAP) & 1)
		drive->dev_flags |= IDE_DFLAG_DSC_OVERLAP;
	else
		drive->dev_flags &= ~IDE_DFLAG_DSC_OVERLAP;

	if ((arg >> IDE_NICE_1) & 1)
		drive->dev_flags |= IDE_DFLAG_NICE1;
	else
		drive->dev_flags &= ~IDE_DFLAG_NICE1;

	return 0;
}