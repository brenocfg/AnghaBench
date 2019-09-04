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
typedef  int u16 ;
struct rtsx_ucr {scalar_t__* cmd_buf; } ;

/* Variables and functions */
 size_t PACKET_TYPE ; 
 scalar_t__ SEQ_WRITE ; 
 size_t STAGE_FLAG ; 
 scalar_t__ STAGE_R ; 
 int /*<<< orphan*/  rtsx_usb_cmd_hdr_tag (struct rtsx_ucr*) ; 

__attribute__((used)) static inline void rtsx_usb_seq_cmd_hdr(struct rtsx_ucr *ucr,
		u16 addr, u16 len, u8 seq_type)
{
	rtsx_usb_cmd_hdr_tag(ucr);

	ucr->cmd_buf[PACKET_TYPE] = seq_type;
	ucr->cmd_buf[5] = (u8)(len >> 8);
	ucr->cmd_buf[6] = (u8)len;
	ucr->cmd_buf[8] = (u8)(addr >> 8);
	ucr->cmd_buf[9] = (u8)addr;

	if (seq_type == SEQ_WRITE)
		ucr->cmd_buf[STAGE_FLAG] = 0;
	else
		ucr->cmd_buf[STAGE_FLAG] = STAGE_R;
}