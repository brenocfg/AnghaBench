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
typedef  int u32 ;

/* Variables and functions */

__attribute__((used)) static int postprocess_read(u32 data, int where, unsigned int size)
{
	u32 ret;

	ret = 0;
	switch (size) {
	case 1:
		ret = (data >> ((where & 3) << 3)) & 0xff;
		break;
	case 2:
		ret = (data >> ((where & 3) << 3)) & 0xffff;
		break;
	case 4:
		ret = data;
		break;
	}
	return ret;
}