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
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_3__ {int /*<<< orphan*/  sect; int /*<<< orphan*/  head; int /*<<< orphan*/  cyl; int /*<<< orphan*/ * id; } ;
typedef  TYPE_1__ ide_drive_t ;

/* Variables and functions */
 size_t ATA_ID_CUR_CYLS ; 
 size_t ATA_ID_CUR_HEADS ; 
 size_t ATA_ID_CUR_SECTORS ; 
 size_t ATA_ID_CYLS ; 
 size_t ATA_ID_HEADS ; 
 size_t ATA_ID_SECTORS ; 

__attribute__((used)) static void generic_id(ide_drive_t *drive)
{
	u16 *id = drive->id;

	id[ATA_ID_CUR_CYLS]	= id[ATA_ID_CYLS]	= drive->cyl;
	id[ATA_ID_CUR_HEADS]	= id[ATA_ID_HEADS]	= drive->head;
	id[ATA_ID_CUR_SECTORS]	= id[ATA_ID_SECTORS]	= drive->sect;
}