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
typedef  int u32 ;
struct packed_hdmi_infoframe {int header; int subpack0_low; int subpack0_high; int subpack1_low; int subpack1_high; } ;
typedef  int ssize_t ;

/* Variables and functions */

void pack_hdmi_infoframe(struct packed_hdmi_infoframe *packed_frame,
			 u8 *raw_frame, ssize_t len)
{
	u32 header = 0;
	u32 subpack0_low = 0;
	u32 subpack0_high = 0;
	u32 subpack1_low = 0;
	u32 subpack1_high = 0;

	switch (len) {
		/*
		 * "When in doubt, use brute force."
		 *     -- Ken Thompson.
		 */
	default:
		/*
		 * We presume that no valid frame is longer than 17
		 * octets, including header...  And truncate to that
		 * if it's longer.
		 */
	case 17:
		subpack1_high = (raw_frame[16] << 16);
	case 16:
		subpack1_high |= (raw_frame[15] << 8);
	case 15:
		subpack1_high |= raw_frame[14];
	case 14:
		subpack1_low = (raw_frame[13] << 24);
	case 13:
		subpack1_low |= (raw_frame[12] << 16);
	case 12:
		subpack1_low |= (raw_frame[11] << 8);
	case 11:
		subpack1_low |= raw_frame[10];
	case 10:
		subpack0_high = (raw_frame[9] << 16);
	case 9:
		subpack0_high |= (raw_frame[8] << 8);
	case 8:
		subpack0_high |= raw_frame[7];
	case 7:
		subpack0_low = (raw_frame[6] << 24);
	case 6:
		subpack0_low |= (raw_frame[5] << 16);
	case 5:
		subpack0_low |= (raw_frame[4] << 8);
	case 4:
		subpack0_low |= raw_frame[3];
	case 3:
		header = (raw_frame[2] << 16);
	case 2:
		header |= (raw_frame[1] << 8);
	case 1:
		header |= raw_frame[0];
	case 0:
		break;
	}

	packed_frame->header = header;
	packed_frame->subpack0_low = subpack0_low;
	packed_frame->subpack0_high = subpack0_high;
	packed_frame->subpack1_low = subpack1_low;
	packed_frame->subpack1_high = subpack1_high;
}