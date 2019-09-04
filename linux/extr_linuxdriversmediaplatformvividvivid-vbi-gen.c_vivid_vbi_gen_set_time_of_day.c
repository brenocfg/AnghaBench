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
typedef  int u8 ;
struct tm {int tm_min; int tm_hour; int tm_mday; int tm_mon; int tm_wday; int tm_year; } ;
struct TYPE_2__ {int tz_minuteswest; } ;

/* Variables and functions */
 int calc_parity (int) ; 
 int /*<<< orphan*/  ktime_get_real_seconds () ; 
 TYPE_1__ sys_tz ; 
 int /*<<< orphan*/  time64_to_tm (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct tm*) ; 

__attribute__((used)) static void vivid_vbi_gen_set_time_of_day(u8 *packet)
{
	struct tm tm;
	u8 checksum, i;

	time64_to_tm(ktime_get_real_seconds(), 0, &tm);
	packet[0] = calc_parity(0x07);
	packet[1] = calc_parity(0x01);
	packet[2] = calc_parity(0x40 | tm.tm_min);
	packet[3] = calc_parity(0x40 | tm.tm_hour);
	packet[4] = calc_parity(0x40 | tm.tm_mday);
	if (tm.tm_mday == 1 && tm.tm_mon == 2 &&
	    sys_tz.tz_minuteswest > tm.tm_min + tm.tm_hour * 60)
		packet[4] = calc_parity(0x60 | tm.tm_mday);
	packet[5] = calc_parity(0x40 | (1 + tm.tm_mon));
	packet[6] = calc_parity(0x40 | (1 + tm.tm_wday));
	packet[7] = calc_parity(0x40 | ((tm.tm_year - 90) & 0x3f));
	packet[8] = calc_parity(0x0f);
	for (checksum = i = 0; i <= 8; i++)
		checksum += packet[i] & 0x7f;
	packet[9] = calc_parity(0x100 - checksum);
	checksum = 0;
	packet[10] = calc_parity(0x07);
	packet[11] = calc_parity(0x04);
	if (sys_tz.tz_minuteswest >= 0)
		packet[12] = calc_parity(0x40 | ((sys_tz.tz_minuteswest / 60) & 0x1f));
	else
		packet[12] = calc_parity(0x40 | ((24 + sys_tz.tz_minuteswest / 60) & 0x1f));
	packet[13] = calc_parity(0);
	packet[14] = calc_parity(0x0f);
	for (checksum = 0, i = 10; i <= 14; i++)
		checksum += packet[i] & 0x7f;
	packet[15] = calc_parity(0x100 - checksum);
}