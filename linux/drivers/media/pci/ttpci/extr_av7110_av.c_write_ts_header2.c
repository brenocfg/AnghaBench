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

/* Variables and functions */
 int TS_SIZE ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 

__attribute__((used)) static int write_ts_header2(u16 pid, u8 *counter, int pes_start, u8 *buf, u8 length)
{
	int i;
	int c = 0;
	int fill;
	u8 tshead[4] = { 0x47, 0x00, 0x00, 0x10 };

	fill = (TS_SIZE - 4) - length;
	if (pes_start)
		tshead[1] = 0x40;
	if (fill)
		tshead[3] = 0x30;
	tshead[1] |= (u8)((pid & 0x1F00) >> 8);
	tshead[2] |= (u8)(pid & 0x00FF);
	tshead[3] |= ((*counter)++ & 0x0F);
	memcpy(buf, tshead, 4);
	c += 4;

	if (fill) {
		buf[4] = fill - 1;
		c++;
		if (fill > 1) {
			buf[5] = 0x00;
			c++;
		}
		for (i = 6; i < fill + 4; i++) {
			buf[i] = 0xFF;
			c++;
		}
	}

	return c;
}