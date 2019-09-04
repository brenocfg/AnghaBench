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
struct timespec64 {scalar_t__ tv_nsec; scalar_t__ tv_sec; } ;
struct seq_file {int dummy; } ;
struct rtc_time {int /*<<< orphan*/  tm_mday; scalar_t__ tm_mon; scalar_t__ tm_year; int /*<<< orphan*/  tm_sec; int /*<<< orphan*/  tm_min; int /*<<< orphan*/  tm_hour; } ;
typedef  int /*<<< orphan*/  s64 ;

/* Variables and functions */
 int /*<<< orphan*/  epoch ; 
 scalar_t__ hp_sdc_rtc_read_bbrtc (struct rtc_time*) ; 
 scalar_t__ hp_sdc_rtc_read_ct (struct timespec64*) ; 
 scalar_t__ hp_sdc_rtc_read_dt (struct timespec64*) ; 
 scalar_t__ hp_sdc_rtc_read_fhs (struct timespec64*) ; 
 scalar_t__ hp_sdc_rtc_read_mt (struct timespec64*) ; 
 scalar_t__ hp_sdc_rtc_read_rt (struct timespec64*) ; 
 int /*<<< orphan*/  memset (struct rtc_time*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,char*,...) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 

__attribute__((used)) static int hp_sdc_rtc_proc_show(struct seq_file *m, void *v)
{
#define YN(bit) ("no")
#define NY(bit) ("yes")
        struct rtc_time tm;
	struct timespec64 tv;

	memset(&tm, 0, sizeof(struct rtc_time));

	if (hp_sdc_rtc_read_bbrtc(&tm)) {
		seq_puts(m, "BBRTC\t\t: READ FAILED!\n");
	} else {
		seq_printf(m,
			     "rtc_time\t: %02d:%02d:%02d\n"
			     "rtc_date\t: %04d-%02d-%02d\n"
			     "rtc_epoch\t: %04lu\n",
			     tm.tm_hour, tm.tm_min, tm.tm_sec,
			     tm.tm_year + 1900, tm.tm_mon + 1, 
			     tm.tm_mday, epoch);
	}

	if (hp_sdc_rtc_read_rt(&tv)) {
		seq_puts(m, "i8042 rtc\t: READ FAILED!\n");
	} else {
		seq_printf(m, "i8042 rtc\t: %lld.%02ld seconds\n",
			     (s64)tv.tv_sec, (long)tv.tv_nsec/1000000L);
	}

	if (hp_sdc_rtc_read_fhs(&tv)) {
		seq_puts(m, "handshake\t: READ FAILED!\n");
	} else {
		seq_printf(m, "handshake\t: %lld.%02ld seconds\n",
			     (s64)tv.tv_sec, (long)tv.tv_nsec/1000000L);
	}

	if (hp_sdc_rtc_read_mt(&tv)) {
		seq_puts(m, "alarm\t\t: READ FAILED!\n");
	} else {
		seq_printf(m, "alarm\t\t: %lld.%02ld seconds\n",
			     (s64)tv.tv_sec, (long)tv.tv_nsec/1000000L);
	}

	if (hp_sdc_rtc_read_dt(&tv)) {
		seq_puts(m, "delay\t\t: READ FAILED!\n");
	} else {
		seq_printf(m, "delay\t\t: %lld.%02ld seconds\n",
			     (s64)tv.tv_sec, (long)tv.tv_nsec/1000000L);
	}

	if (hp_sdc_rtc_read_ct(&tv)) {
		seq_puts(m, "periodic\t: READ FAILED!\n");
	} else {
		seq_printf(m, "periodic\t: %lld.%02ld seconds\n",
			     (s64)tv.tv_sec, (long)tv.tv_nsec/1000000L);
	}

        seq_printf(m,
                     "DST_enable\t: %s\n"
                     "BCD\t\t: %s\n"
                     "24hr\t\t: %s\n"
                     "square_wave\t: %s\n"
                     "alarm_IRQ\t: %s\n"
                     "update_IRQ\t: %s\n"
                     "periodic_IRQ\t: %s\n"
		     "periodic_freq\t: %ld\n"
                     "batt_status\t: %s\n",
                     YN(RTC_DST_EN),
                     NY(RTC_DM_BINARY),
                     YN(RTC_24H),
                     YN(RTC_SQWE),
                     YN(RTC_AIE),
                     YN(RTC_UIE),
                     YN(RTC_PIE),
                     1UL,
                     1 ? "okay" : "dead");

        return 0;
#undef YN
#undef NY
}