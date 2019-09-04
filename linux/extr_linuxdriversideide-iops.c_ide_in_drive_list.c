#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct drive_list_entry {int /*<<< orphan*/  id_firmware; scalar_t__ id_model; } ;

/* Variables and functions */
 size_t ATA_ID_FW_REV ; 
 size_t ATA_ID_PROD ; 
 int /*<<< orphan*/  strcmp (scalar_t__,char*) ; 
 scalar_t__ strstr (char*,int /*<<< orphan*/ ) ; 

int ide_in_drive_list(u16 *id, const struct drive_list_entry *table)
{
	for ( ; table->id_model; table++)
		if ((!strcmp(table->id_model, (char *)&id[ATA_ID_PROD])) &&
		    (!table->id_firmware ||
		     strstr((char *)&id[ATA_ID_FW_REV], table->id_firmware)))
			return 1;
	return 0;
}