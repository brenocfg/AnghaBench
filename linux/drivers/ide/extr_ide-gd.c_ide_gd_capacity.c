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
typedef  int /*<<< orphan*/  sector_t ;
struct TYPE_3__ {int /*<<< orphan*/  capacity64; } ;
typedef  TYPE_1__ ide_drive_t ;

/* Variables and functions */

sector_t ide_gd_capacity(ide_drive_t *drive)
{
	return drive->capacity64;
}