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
typedef  enum dpcd_downstream_port_max_bpc { ____Placeholder_dpcd_downstream_port_max_bpc } dpcd_downstream_port_max_bpc ;

/* Variables and functions */
#define  DOWN_STREAM_MAX_10BPC 131 
#define  DOWN_STREAM_MAX_12BPC 130 
#define  DOWN_STREAM_MAX_16BPC 129 
#define  DOWN_STREAM_MAX_8BPC 128 

__attribute__((used)) static int translate_dpcd_max_bpc(enum dpcd_downstream_port_max_bpc bpc)
{
	switch (bpc) {
	case DOWN_STREAM_MAX_8BPC:
		return 8;
	case DOWN_STREAM_MAX_10BPC:
		return 10;
	case DOWN_STREAM_MAX_12BPC:
		return 12;
	case DOWN_STREAM_MAX_16BPC:
		return 16;
	default:
		break;
	}

	return -1;
}