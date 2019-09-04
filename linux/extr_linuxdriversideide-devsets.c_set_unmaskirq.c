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
struct TYPE_3__ {int dev_flags; } ;
typedef  TYPE_1__ ide_drive_t ;

/* Variables and functions */
 int EINVAL ; 
 int EPERM ; 
 int IDE_DFLAG_NO_UNMASK ; 
 int IDE_DFLAG_UNMASK ; 

__attribute__((used)) static int set_unmaskirq(ide_drive_t *drive, int arg)
{
	if (drive->dev_flags & IDE_DFLAG_NO_UNMASK)
		return -EPERM;

	if (arg < 0 || arg > 1)
		return -EINVAL;

	if (arg)
		drive->dev_flags |= IDE_DFLAG_UNMASK;
	else
		drive->dev_flags &= ~IDE_DFLAG_UNMASK;

	return 0;
}