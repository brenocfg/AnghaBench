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
typedef  int u16 ;
struct rtsx_ucr {int cmd_idx; int* cmd_buf; } ;

/* Variables and functions */
 int CMD_OFFSET ; 
 int IOBUF_SIZE ; 

void rtsx_usb_add_cmd(struct rtsx_ucr *ucr, u8 cmd_type, u16 reg_addr,
		u8 mask, u8 data)
{
	int i;

	if (ucr->cmd_idx < (IOBUF_SIZE - CMD_OFFSET) / 4) {
		i = CMD_OFFSET + ucr->cmd_idx * 4;

		ucr->cmd_buf[i++] = ((cmd_type & 0x03) << 6) |
			(u8)((reg_addr >> 8) & 0x3F);
		ucr->cmd_buf[i++] = (u8)reg_addr;
		ucr->cmd_buf[i++] = mask;
		ucr->cmd_buf[i++] = data;

		ucr->cmd_idx++;
	}
}