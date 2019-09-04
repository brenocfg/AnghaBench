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
struct request {int dummy; } ;
typedef  int /*<<< orphan*/  sector_t ;
typedef  int /*<<< orphan*/  ide_startstop_t ;
struct TYPE_6__ {TYPE_1__* disk_ops; } ;
typedef  TYPE_2__ ide_drive_t ;
struct TYPE_5__ {int /*<<< orphan*/  (* do_request ) (TYPE_2__*,struct request*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_2__*,struct request*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ide_startstop_t ide_gd_do_request(ide_drive_t *drive,
					 struct request *rq, sector_t sector)
{
	return drive->disk_ops->do_request(drive, rq, sector);
}