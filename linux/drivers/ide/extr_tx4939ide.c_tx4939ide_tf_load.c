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
typedef  int u8 ;
struct ide_taskfile {int dummy; } ;
typedef  int /*<<< orphan*/  ide_drive_t ;

/* Variables and functions */
 int IDE_VALID_DEVICE ; 
 int /*<<< orphan*/  ide_tf_load (int /*<<< orphan*/ *,struct ide_taskfile*,int) ; 
 int /*<<< orphan*/  tx4939ide_tf_load_fixup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void tx4939ide_tf_load(ide_drive_t *drive, struct ide_taskfile *tf,
			      u8 valid)
{
	ide_tf_load(drive, tf, valid);

	if (valid & IDE_VALID_DEVICE)
		tx4939ide_tf_load_fixup(drive);
}