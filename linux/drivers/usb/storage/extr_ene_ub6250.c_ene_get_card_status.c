#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct us_data {scalar_t__ extra; } ;
struct TYPE_2__ {scalar_t__ IsMMC; scalar_t__ HiCapacity; } ;
struct ene_ub6250_info {int SD_READ_BL_LEN; int HC_C_SIZE; int SD_C_SIZE; int SD_C_SIZE_MULT; int SD_Block_Mult; TYPE_1__ SD_Status; } ;

/* Variables and functions */
 scalar_t__ SD_BLOCK_LEN ; 
 int USB_STOR_TRANSPORT_GOOD ; 

__attribute__((used)) static int ene_get_card_status(struct us_data *us, u8 *buf)
{
	u16 tmpreg;
	u32 reg4b;
	struct ene_ub6250_info *info = (struct ene_ub6250_info *) us->extra;

	/*usb_stor_dbg(us, "transport --- ENE_ReadSDReg\n");*/
	reg4b = *(u32 *)&buf[0x18];
	info->SD_READ_BL_LEN = (u8)((reg4b >> 8) & 0x0f);

	tmpreg = (u16) reg4b;
	reg4b = *(u32 *)(&buf[0x14]);
	if (info->SD_Status.HiCapacity && !info->SD_Status.IsMMC)
		info->HC_C_SIZE = (reg4b >> 8) & 0x3fffff;

	info->SD_C_SIZE = ((tmpreg & 0x03) << 10) | (u16)(reg4b >> 22);
	info->SD_C_SIZE_MULT = (u8)(reg4b >> 7)  & 0x07;
	if (info->SD_Status.HiCapacity && info->SD_Status.IsMMC)
		info->HC_C_SIZE = *(u32 *)(&buf[0x100]);

	if (info->SD_READ_BL_LEN > SD_BLOCK_LEN) {
		info->SD_Block_Mult = 1 << (info->SD_READ_BL_LEN-SD_BLOCK_LEN);
		info->SD_READ_BL_LEN = SD_BLOCK_LEN;
	} else {
		info->SD_Block_Mult = 1;
	}

	return USB_STOR_TRANSPORT_GOOD;
}