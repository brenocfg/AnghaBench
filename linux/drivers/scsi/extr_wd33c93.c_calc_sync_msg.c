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
typedef  unsigned int uchar ;

/* Variables and functions */

__attribute__((used)) static inline void
calc_sync_msg(unsigned int period, unsigned int offset, unsigned int fast,
                uchar  msg[2])
{
	/* 'period' is a "normal"-mode value, like the ones in 'sx_table'. The
	 * actually used transfer period for Fast SCSI synchronous data
	 * transfers is half that value.
	 */
	period /= 4;
	if (offset && fast)
		period /= 2;
	msg[0] = period;
	msg[1] = offset;
}