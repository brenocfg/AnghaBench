#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int flags; } ;
struct wiimote_data {int /*<<< orphan*/  ir; TYPE_1__ state; } ;
typedef  int __u8 ;
typedef  int __u16 ;

/* Variables and functions */
 int ABS_HAT0X ; 
 int ABS_HAT0Y ; 
 int ABS_HAT1X ; 
 int ABS_HAT1Y ; 
 int ABS_HAT2X ; 
 int ABS_HAT2Y ; 
 int ABS_HAT3X ; 
 int ABS_HAT3Y ; 
 int WIIPROTO_FLAGS_IR ; 
 int /*<<< orphan*/  input_report_abs (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wiimod_ir_in_ir(struct wiimote_data *wdata, const __u8 *ir,
			    bool packed, unsigned int id)
{
	__u16 x, y;
	__u8 xid, yid;
	bool sync = false;

	if (!(wdata->state.flags & WIIPROTO_FLAGS_IR))
		return;

	switch (id) {
	case 0:
		xid = ABS_HAT0X;
		yid = ABS_HAT0Y;
		break;
	case 1:
		xid = ABS_HAT1X;
		yid = ABS_HAT1Y;
		break;
	case 2:
		xid = ABS_HAT2X;
		yid = ABS_HAT2Y;
		break;
	case 3:
		xid = ABS_HAT3X;
		yid = ABS_HAT3Y;
		sync = true;
		break;
	default:
		return;
	}

	/*
	 * Basic IR data is encoded into 3 bytes. The first two bytes are the
	 * lower 8 bit of the X/Y data, the 3rd byte contains the upper 2 bits
	 * of both.
	 * If data is packed, then the 3rd byte is put first and slightly
	 * reordered. This allows to interleave packed and non-packed data to
	 * have two IR sets in 5 bytes instead of 6.
	 * The resulting 10bit X/Y values are passed to the ABS_HAT? input dev.
	 */

	if (packed) {
		x = ir[1] | ((ir[0] & 0x03) << 8);
		y = ir[2] | ((ir[0] & 0x0c) << 6);
	} else {
		x = ir[0] | ((ir[2] & 0x30) << 4);
		y = ir[1] | ((ir[2] & 0xc0) << 2);
	}

	input_report_abs(wdata->ir, xid, x);
	input_report_abs(wdata->ir, yid, y);

	if (sync)
		input_sync(wdata->ir);
}