#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int flags; } ;
struct ata_eh_context {TYPE_2__ i; } ;
struct ata_device {scalar_t__ class; TYPE_1__* link; } ;
struct TYPE_3__ {struct ata_eh_context eh_context; } ;

/* Variables and functions */
 scalar_t__ ATA_DEV_ATAPI ; 
 int ATA_EHI_PRINTINFO ; 
 int /*<<< orphan*/  ali_atapi_dma ; 
 int /*<<< orphan*/  ata_dev_warn (struct ata_device*,char*) ; 

__attribute__((used)) static void ali_warn_atapi_dma(struct ata_device *adev)
{
	struct ata_eh_context *ehc = &adev->link->eh_context;
	int print_info = ehc->i.flags & ATA_EHI_PRINTINFO;

	if (print_info && adev->class == ATA_DEV_ATAPI && !ali_atapi_dma) {
		ata_dev_warn(adev,
			     "WARNING: ATAPI DMA disabled for reliability issues.  It can be enabled\n");
		ata_dev_warn(adev,
			     "WARNING: via pata_ali.atapi_dma modparam or corresponding sysfs node.\n");
	}
}