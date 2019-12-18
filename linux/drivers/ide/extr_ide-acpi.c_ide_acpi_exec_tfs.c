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
struct TYPE_5__ {int name; int /*<<< orphan*/  dn; } ;
typedef  TYPE_1__ ide_drive_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEBPRINT (char*,int,...) ; 
 int do_drive_get_GTF (TYPE_1__*,unsigned int*,unsigned long*,unsigned long*) ; 
 int do_drive_set_taskfiles (TYPE_1__*,unsigned int,unsigned long) ; 
 int /*<<< orphan*/  kfree (void*) ; 

int ide_acpi_exec_tfs(ide_drive_t *drive)
{
	int		ret;
	unsigned int	gtf_length;
	unsigned long	gtf_address;
	unsigned long	obj_loc;

	DEBPRINT("call get_GTF, drive=%s port=%d\n", drive->name, drive->dn);

	ret = do_drive_get_GTF(drive, &gtf_length, &gtf_address, &obj_loc);
	if (ret < 0) {
		DEBPRINT("get_GTF error (%d)\n", ret);
		return ret;
	}

	DEBPRINT("call set_taskfiles, drive=%s\n", drive->name);

	ret = do_drive_set_taskfiles(drive, gtf_length, gtf_address);
	kfree((void *)obj_loc);
	if (ret < 0) {
		DEBPRINT("set_taskfiles error (%d)\n", ret);
	}

	DEBPRINT("ret=%d\n", ret);

	return ret;
}