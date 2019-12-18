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
struct request {int dummy; } ;
typedef  int /*<<< orphan*/  ide_startstop_t ;
struct TYPE_5__ {scalar_t__ media; } ;
typedef  TYPE_1__ ide_drive_t ;

/* Variables and functions */
 int /*<<< orphan*/  ide_ata_error (TYPE_1__*,struct request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ide_atapi_error (TYPE_1__*,struct request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ide_disk ; 

__attribute__((used)) static ide_startstop_t __ide_error(ide_drive_t *drive, struct request *rq,
				   u8 stat, u8 err)
{
	if (drive->media == ide_disk)
		return ide_ata_error(drive, rq, stat, err);
	return ide_atapi_error(drive, rq, stat, err);
}