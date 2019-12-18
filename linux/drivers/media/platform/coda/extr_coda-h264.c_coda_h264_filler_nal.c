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

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  memset (char*,int,int) ; 

int coda_h264_filler_nal(int size, char *p)
{
	if (size < 6)
		return -EINVAL;

	p[0] = 0x00;
	p[1] = 0x00;
	p[2] = 0x00;
	p[3] = 0x01;
	p[4] = 0x0c;
	memset(p + 5, 0xff, size - 6);
	/* Add rbsp stop bit and trailing at the end */
	p[size - 1] = 0x80;

	return 0;
}