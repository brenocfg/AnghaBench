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
typedef  int /*<<< orphan*/  ide_hwif_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_CBL_PATA80 ; 

__attribute__((used)) static u8 palm_bk3710_cable_detect(ide_hwif_t *hwif)
{
	return ATA_CBL_PATA80;
}