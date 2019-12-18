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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  ide_drive_t ;

/* Variables and functions */
 scalar_t__ ATA_133 ; 
 scalar_t__ chipset_family ; 
 int /*<<< orphan*/  sis_ata133_program_udma_timings (int /*<<< orphan*/ *,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  sis_ata33_program_udma_timings (int /*<<< orphan*/ *,int /*<<< orphan*/  const) ; 

__attribute__((used)) static void sis_program_udma_timings(ide_drive_t *drive, const u8 mode)
{
	if (chipset_family >= ATA_133)	/* ATA_133 */
		sis_ata133_program_udma_timings(drive, mode);
	else				/* ATA_33/66/100a/100/133a */
		sis_ata33_program_udma_timings(drive, mode);
}