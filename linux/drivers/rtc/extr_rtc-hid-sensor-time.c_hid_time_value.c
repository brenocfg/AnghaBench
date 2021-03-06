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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;

/* Variables and functions */

__attribute__((used)) static u32 hid_time_value(size_t raw_len, char *raw_data)
{
	switch (raw_len) {
	case 1:
		return *(u8 *)raw_data;
	case 2:
		return *(u16 *)raw_data;
	case 4:
		return *(u32 *)raw_data;
	default:
		return (u32)(~0U); /* 0xff... or -1 to denote an error */
	}
}