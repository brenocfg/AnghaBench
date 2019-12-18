#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_5__ {scalar_t__ channel; } ;
typedef  TYPE_1__ ide_hwif_t ;
struct TYPE_6__ {int dma_mode; } ;
typedef  TYPE_2__ ide_drive_t ;

/* Variables and functions */
 int BUSMASTER_TIMEOUT ; 
 int /*<<< orphan*/  CY82_DATA_PORT ; 
 int CY82_INDEX_CHANNEL0 ; 
 int CY82_INDEX_CHANNEL1 ; 
 int /*<<< orphan*/  CY82_INDEX_PORT ; 
 int CY82_INDEX_TIMEOUT ; 
 int /*<<< orphan*/  outb (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cy82c693_set_dma_mode(ide_hwif_t *hwif, ide_drive_t *drive)
{
	const u8 mode = drive->dma_mode;
	u8 single = (mode & 0x10) >> 4, index = 0, data = 0;

	index = hwif->channel ? CY82_INDEX_CHANNEL1 : CY82_INDEX_CHANNEL0;

	data = (mode & 3) | (single << 2);

	outb(index, CY82_INDEX_PORT);
	outb(data, CY82_DATA_PORT);

	/*
	 * note: below we set the value for Bus Master IDE TimeOut Register
	 * I'm not absolutely sure what this does, but it solved my problem
	 * with IDE DMA and sound, so I now can play sound and work with
	 * my IDE driver at the same time :-)
	 *
	 * If you know the correct (best) value for this register please
	 * let me know - ASK
	 */

	data = BUSMASTER_TIMEOUT;
	outb(CY82_INDEX_TIMEOUT, CY82_INDEX_PORT);
	outb(data, CY82_DATA_PORT);
}