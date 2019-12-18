#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct ide_cmd {int tf_flags; } ;
struct TYPE_7__ {scalar_t__ media; TYPE_2__* hwif; } ;
typedef  TYPE_3__ ide_drive_t ;
struct TYPE_5__ {unsigned long data_addr; } ;
struct TYPE_6__ {TYPE_1__ io_ports; } ;

/* Variables and functions */
 int IDE_TFLAG_FS ; 
 int /*<<< orphan*/  __ide_mm_insw (unsigned long,void*,unsigned int) ; 
 scalar_t__ ide_disk ; 
 int /*<<< orphan*/  raw_insw_swapw (int /*<<< orphan*/ *,void*,unsigned int) ; 

__attribute__((used)) static void falconide_input_data(ide_drive_t *drive, struct ide_cmd *cmd,
				 void *buf, unsigned int len)
{
	unsigned long data_addr = drive->hwif->io_ports.data_addr;

	if (drive->media == ide_disk && cmd && (cmd->tf_flags & IDE_TFLAG_FS)) {
		__ide_mm_insw(data_addr, buf, (len + 1) / 2);
		return;
	}

	raw_insw_swapw((u16 *)data_addr, buf, (len + 1) / 2);
}