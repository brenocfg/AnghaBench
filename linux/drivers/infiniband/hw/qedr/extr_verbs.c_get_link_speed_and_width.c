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

/* Variables and functions */
 int /*<<< orphan*/  IB_SPEED_DDR ; 
 int /*<<< orphan*/  IB_SPEED_EDR ; 
 int /*<<< orphan*/  IB_SPEED_HDR ; 
 int /*<<< orphan*/  IB_SPEED_QDR ; 
 int /*<<< orphan*/  IB_SPEED_SDR ; 
 int /*<<< orphan*/  IB_WIDTH_1X ; 
 int /*<<< orphan*/  IB_WIDTH_4X ; 

__attribute__((used)) static inline void get_link_speed_and_width(int speed, u8 *ib_speed,
					    u8 *ib_width)
{
	switch (speed) {
	case 1000:
		*ib_speed = IB_SPEED_SDR;
		*ib_width = IB_WIDTH_1X;
		break;
	case 10000:
		*ib_speed = IB_SPEED_QDR;
		*ib_width = IB_WIDTH_1X;
		break;

	case 20000:
		*ib_speed = IB_SPEED_DDR;
		*ib_width = IB_WIDTH_4X;
		break;

	case 25000:
		*ib_speed = IB_SPEED_EDR;
		*ib_width = IB_WIDTH_1X;
		break;

	case 40000:
		*ib_speed = IB_SPEED_QDR;
		*ib_width = IB_WIDTH_4X;
		break;

	case 50000:
		*ib_speed = IB_SPEED_HDR;
		*ib_width = IB_WIDTH_1X;
		break;

	case 100000:
		*ib_speed = IB_SPEED_EDR;
		*ib_width = IB_WIDTH_4X;
		break;

	default:
		/* Unsupported */
		*ib_speed = IB_SPEED_SDR;
		*ib_width = IB_WIDTH_1X;
	}
}