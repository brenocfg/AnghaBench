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
typedef  int /*<<< orphan*/  ide_drive_t ;

/* Variables and functions */
 int /*<<< orphan*/  ide_dma_start (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ns87415_prepare_drive (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void ns87415_dma_start(ide_drive_t *drive)
{
	ns87415_prepare_drive(drive, 1);
	ide_dma_start(drive);
}