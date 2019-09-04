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
struct ide_cmd {int tf_flags; } ;
typedef  int /*<<< orphan*/  ide_drive_t ;

/* Variables and functions */
 int IDE_TFLAG_WRITE ; 
 int IOC4_DMA_READ ; 
 int IOC4_DMA_WRITE ; 
 scalar_t__ sgiioc4_build_dmatable (int /*<<< orphan*/ *,struct ide_cmd*) ; 
 int /*<<< orphan*/  sgiioc4_configure_for_dma (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sgiioc4_dma_setup(ide_drive_t *drive, struct ide_cmd *cmd)
{
	int ddir;
	u8 write = !!(cmd->tf_flags & IDE_TFLAG_WRITE);

	if (sgiioc4_build_dmatable(drive, cmd) == 0)
		/* try PIO instead of DMA */
		return 1;

	if (write)
		/* Writes TO the IOC4 FROM Main Memory */
		ddir = IOC4_DMA_READ;
	else
		/* Writes FROM the IOC4 TO Main Memory */
		ddir = IOC4_DMA_WRITE;

	sgiioc4_configure_for_dma(ddir, drive);

	return 0;
}