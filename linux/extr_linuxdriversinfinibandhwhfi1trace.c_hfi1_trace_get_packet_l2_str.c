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

const char *hfi1_trace_get_packet_l2_str(u8 l2)
{
	switch (l2) {
	case 0:
		return "0";
	case 1:
		return "1";
	case 2:
		return "16B";
	case 3:
		return "9B";
	}
	return "";
}