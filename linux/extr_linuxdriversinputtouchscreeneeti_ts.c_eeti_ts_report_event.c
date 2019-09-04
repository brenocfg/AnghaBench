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
typedef  unsigned int u16 ;
struct eeti_ts {int /*<<< orphan*/  input; int /*<<< orphan*/  props; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_PRESSURE ; 
 int /*<<< orphan*/  BTN_TOUCH ; 
 unsigned int EETI_TS_BITDEPTH ; 
 int REPORT_BIT_AD0 ; 
 int REPORT_BIT_AD1 ; 
 int REPORT_BIT_HAS_PRESSURE ; 
 int REPORT_BIT_PRESSED ; 
 unsigned int REPORT_RES_BITS (int) ; 
 unsigned int get_unaligned_be16 (int*) ; 
 int /*<<< orphan*/  input_report_abs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_report_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  touchscreen_report_pos (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int,unsigned int,int) ; 

__attribute__((used)) static void eeti_ts_report_event(struct eeti_ts *eeti, u8 *buf)
{
	unsigned int res;
	u16 x, y;

	res = REPORT_RES_BITS(buf[0] & (REPORT_BIT_AD0 | REPORT_BIT_AD1));

	x = get_unaligned_be16(&buf[1]);
	y = get_unaligned_be16(&buf[3]);

	/* fix the range to 11 bits */
	x >>= res - EETI_TS_BITDEPTH;
	y >>= res - EETI_TS_BITDEPTH;

	if (buf[0] & REPORT_BIT_HAS_PRESSURE)
		input_report_abs(eeti->input, ABS_PRESSURE, buf[5]);

	touchscreen_report_pos(eeti->input, &eeti->props, x, y, false);
	input_report_key(eeti->input, BTN_TOUCH, buf[0] & REPORT_BIT_PRESSED);
	input_sync(eeti->input);
}