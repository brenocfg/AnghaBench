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
typedef  scalar_t__ u8 ;
struct rtsx_pcr {scalar_t__ sd30_drive_sel_3v3; scalar_t__ sd30_drive_sel_1v8; } ;

/* Variables and functions */
 scalar_t__ OUTPUT_3V3 ; 
 int /*<<< orphan*/  SD30_CLK_DRIVE_SEL ; 
 int /*<<< orphan*/  SD30_CMD_DRIVE_SEL ; 
 int /*<<< orphan*/  rtsx_pci_write_register (struct rtsx_pcr*,int /*<<< orphan*/ ,int,scalar_t__) ; 

__attribute__((used)) static void rts5260_fill_driving(struct rtsx_pcr *pcr, u8 voltage)
{
	u8 driving_3v3[6][3] = {
		{0x94, 0x94, 0x94},
		{0x11, 0x11, 0x18},
		{0x55, 0x55, 0x5C},
		{0x94, 0x94, 0x94},
		{0x94, 0x94, 0x94},
		{0xFF, 0xFF, 0xFF},
	};
	u8 driving_1v8[6][3] = {
		{0x9A, 0x89, 0x89},
		{0xC4, 0xC4, 0xC4},
		{0x3C, 0x3C, 0x3C},
		{0x9B, 0x99, 0x99},
		{0x9A, 0x89, 0x89},
		{0xFE, 0xFE, 0xFE},
	};
	u8 (*driving)[3], drive_sel;

	if (voltage == OUTPUT_3V3) {
		driving = driving_3v3;
		drive_sel = pcr->sd30_drive_sel_3v3;
	} else {
		driving = driving_1v8;
		drive_sel = pcr->sd30_drive_sel_1v8;
	}

	rtsx_pci_write_register(pcr, SD30_CLK_DRIVE_SEL,
			 0xFF, driving[drive_sel][0]);

	rtsx_pci_write_register(pcr, SD30_CMD_DRIVE_SEL,
			 0xFF, driving[drive_sel][1]);

	rtsx_pci_write_register(pcr, SD30_CMD_DRIVE_SEL,
			 0xFF, driving[drive_sel][2]);
}