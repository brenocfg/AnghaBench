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
struct isdnhdlc_vars {int dstpos; int crc; } ;

/* Variables and functions */
 int HDLC_CRC_ERROR ; 
 int HDLC_FRAMING_ERROR ; 

__attribute__((used)) static int
check_frame(struct isdnhdlc_vars *hdlc)
{
	int status;

	if (hdlc->dstpos < 2)	/* too small - framing error */
		status = -HDLC_FRAMING_ERROR;
	else if (hdlc->crc != 0xf0b8)	/* crc error */
		status = -HDLC_CRC_ERROR;
	else {
		/* remove CRC */
		hdlc->dstpos -= 2;
		/* good frame */
		status = hdlc->dstpos;
	}
	return status;
}