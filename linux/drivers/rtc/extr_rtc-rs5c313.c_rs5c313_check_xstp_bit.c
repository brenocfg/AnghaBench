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
struct rtc_time {int tm_mday; int tm_mon; int tm_year; } ;

/* Variables and functions */
 int /*<<< orphan*/  RS5C313_CEDISABLE ; 
 int /*<<< orphan*/  RS5C313_CEENABLE ; 
 int RS5C313_CNTREG_ADJ_BSY ; 
 int RS5C313_CNTREG_WTEN_XSTP ; 
 int /*<<< orphan*/  RS5C313_MISCOP ; 
 int /*<<< orphan*/  memset (struct rtc_time*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ndelay (int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int rs5c313_read_cntreg () ; 
 int /*<<< orphan*/  rs5c313_rtc_set_time (int /*<<< orphan*/ *,struct rtc_time*) ; 
 int /*<<< orphan*/  rs5c313_write_cntreg (int) ; 
 int /*<<< orphan*/  rs5c313_write_intintvreg (int) ; 

__attribute__((used)) static void rs5c313_check_xstp_bit(void)
{
	struct rtc_time tm;
	int cnt;

	RS5C313_CEENABLE;	/* CE:H */
	if (rs5c313_read_cntreg() & RS5C313_CNTREG_WTEN_XSTP) {
		/* INT interval reg. OFF */
		rs5c313_write_intintvreg(0x00);
		/* Initialize control reg. 24 hour & adjust */
		rs5c313_write_cntreg(0x07);

		/* busy check. */
		for (cnt = 0; cnt < 100; cnt++) {
			if (!(rs5c313_read_cntreg() & RS5C313_CNTREG_ADJ_BSY))
				break;
			RS5C313_MISCOP;
		}

		memset(&tm, 0, sizeof(struct rtc_time));
		tm.tm_mday	= 1;
		tm.tm_mon	= 1 - 1;
		tm.tm_year	= 2000 - 1900;

		rs5c313_rtc_set_time(NULL, &tm);
		pr_err("invalid value, resetting to 1 Jan 2000\n");
	}
	RS5C313_CEDISABLE;
	ndelay(700);		/* CE:L */
}