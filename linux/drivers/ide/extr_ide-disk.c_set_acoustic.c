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
struct TYPE_4__ {int acoustic; } ;
typedef  TYPE_1__ ide_drive_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SETFEATURES_AAM_OFF ; 
 int /*<<< orphan*/  SETFEATURES_AAM_ON ; 
 int /*<<< orphan*/  ide_do_setfeature (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int set_acoustic(ide_drive_t *drive, int arg)
{
	if (arg < 0 || arg > 254)
		return -EINVAL;

	ide_do_setfeature(drive,
		arg ? SETFEATURES_AAM_ON : SETFEATURES_AAM_OFF, arg);

	drive->acoustic = arg;

	return 0;
}