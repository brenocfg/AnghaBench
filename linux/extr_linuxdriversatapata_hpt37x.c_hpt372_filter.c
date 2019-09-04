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
struct ata_device {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int ATA_MASK_MWDMA ; 
 int ATA_SHIFT_UDMA ; 
 scalar_t__ ata_id_is_sata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned long hpt372_filter(struct ata_device *adev, unsigned long mask)
{
	if (ata_id_is_sata(adev->id))
		mask &= ~((0xE << ATA_SHIFT_UDMA) | ATA_MASK_MWDMA);

	return mask;
}