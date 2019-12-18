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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  ide_startstop_t ;
struct TYPE_5__ {scalar_t__ max_failures; scalar_t__ failures; } ;
typedef  TYPE_1__ ide_drive_t ;

/* Variables and functions */
 int EBUSY ; 
 int __ide_wait_stat (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ide_error (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ide_stopped ; 

int ide_wait_stat(ide_startstop_t *startstop, ide_drive_t *drive, u8 good,
		  u8 bad, unsigned long timeout)
{
	int err;
	u8 stat;

	/* bail early if we've exceeded max_failures */
	if (drive->max_failures && (drive->failures > drive->max_failures)) {
		*startstop = ide_stopped;
		return 1;
	}

	err = __ide_wait_stat(drive, good, bad, timeout, &stat);

	if (err) {
		char *s = (err == -EBUSY) ? "status timeout" : "status error";
		*startstop = ide_error(drive, s, stat);
	}

	return err;
}