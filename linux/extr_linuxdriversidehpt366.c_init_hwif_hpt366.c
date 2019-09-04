#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct hpt_info {scalar_t__ chip_type; int pci_clk; scalar_t__ dpll_clk; } ;
struct TYPE_5__ {int select_data; int /*<<< orphan*/ * rw_disk; TYPE_1__* host; scalar_t__ channel; int /*<<< orphan*/  dev; } ;
typedef  TYPE_2__ ide_hwif_t ;
struct TYPE_4__ {int /*<<< orphan*/  host_flags; } ;

/* Variables and functions */
 scalar_t__ HPT372N ; 
 int /*<<< orphan*/  IDE_HFLAG_SERIALIZE ; 
 struct hpt_info* hpt3xx_get_info (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hpt3xxn_rw_disk ; 

__attribute__((used)) static void init_hwif_hpt366(ide_hwif_t *hwif)
{
	struct hpt_info *info	= hpt3xx_get_info(hwif->dev);
	u8  chip_type		= info->chip_type;

	/* Cache the channel's MISC. control registers' offset */
	hwif->select_data	= hwif->channel ? 0x54 : 0x50;

	/*
	 * HPT3xxN chips have some complications:
	 *
	 * - on 33 MHz PCI we must clock switch
	 * - on 66 MHz PCI we must NOT use the PCI clock
	 */
	if (chip_type >= HPT372N && info->dpll_clk && info->pci_clk < 66) {
		/*
		 * Clock is shared between the channels,
		 * so we'll have to serialize them... :-(
		 */
		hwif->host->host_flags |= IDE_HFLAG_SERIALIZE;
		hwif->rw_disk = &hpt3xxn_rw_disk;
	}
}