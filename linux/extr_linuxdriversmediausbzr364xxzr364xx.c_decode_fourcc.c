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
typedef  int __u32 ;

/* Variables and functions */

__attribute__((used)) static char *decode_fourcc(__u32 pixelformat, char *buf)
{
	buf[0] = pixelformat & 0xff;
	buf[1] = (pixelformat >> 8) & 0xff;
	buf[2] = (pixelformat >> 16) & 0xff;
	buf[3] = (pixelformat >> 24) & 0xff;
	buf[4] = '\0';
	return buf;
}