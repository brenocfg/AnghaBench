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
struct rtc_time {int dummy; } ;

/* Variables and functions */
 scalar_t__ hp_sdc_rtc_do_read_bbrtc (struct rtc_time*) ; 
 scalar_t__ memcmp (struct rtc_time*,struct rtc_time*,int) ; 
 int /*<<< orphan*/  memcpy (struct rtc_time*,struct rtc_time*,int) ; 

__attribute__((used)) static int hp_sdc_rtc_read_bbrtc (struct rtc_time *rtctm)
{
	struct rtc_time tm, tm_last;
	int i = 0;

	/* MSM-58321 has no read latch, so must read twice and compare. */

	if (hp_sdc_rtc_do_read_bbrtc(&tm_last)) return -1;
	if (hp_sdc_rtc_do_read_bbrtc(&tm)) return -1;

	while (memcmp(&tm, &tm_last, sizeof(struct rtc_time))) {
		if (i++ > 4) return -1;
		memcpy(&tm_last, &tm, sizeof(struct rtc_time));
		if (hp_sdc_rtc_do_read_bbrtc(&tm)) return -1;
	}

	memcpy(rtctm, &tm, sizeof(struct rtc_time));

	return 0;
}