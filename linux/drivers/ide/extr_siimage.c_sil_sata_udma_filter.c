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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_3__ {int /*<<< orphan*/ * id; } ;
typedef  TYPE_1__ ide_drive_t ;

/* Variables and functions */
 size_t ATA_ID_PROD ; 
 int /*<<< orphan*/  ATA_UDMA5 ; 
 int /*<<< orphan*/  ATA_UDMA6 ; 
 scalar_t__ strstr (char*,char*) ; 

__attribute__((used)) static u8 sil_sata_udma_filter(ide_drive_t *drive)
{
	char *m = (char *)&drive->id[ATA_ID_PROD];

	return strstr(m, "Maxtor") ? ATA_UDMA5 : ATA_UDMA6;
}