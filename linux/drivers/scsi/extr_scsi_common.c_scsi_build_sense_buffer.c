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

/* Variables and functions */

void scsi_build_sense_buffer(int desc, u8 *buf, u8 key, u8 asc, u8 ascq)
{
	if (desc) {
		buf[0] = 0x72;	/* descriptor, current */
		buf[1] = key;
		buf[2] = asc;
		buf[3] = ascq;
		buf[7] = 0;
	} else {
		buf[0] = 0x70;	/* fixed, current */
		buf[2] = key;
		buf[7] = 0xa;
		buf[12] = asc;
		buf[13] = ascq;
	}
}