#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct rtc_time {int tm_sec; int tm_min; int tm_hour; int tm_mday; int tm_mon; int tm_year; int tm_isdst; int /*<<< orphan*/  tm_yday; int /*<<< orphan*/  tm_wday; } ;
struct TYPE_5__ {int second; int minute; int hour; int day; int month; int year; int daylight; } ;
typedef  TYPE_1__ efi_time_t ;

/* Variables and functions */
#define  EFI_ISDST 129 
#define  EFI_TIME_ADJUST_DAYLIGHT 128 
 int /*<<< orphan*/  compute_wday (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  compute_yday (TYPE_1__*) ; 
 int /*<<< orphan*/  memset (struct rtc_time*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool
convert_from_efi_time(efi_time_t *eft, struct rtc_time *wtime)
{
	memset(wtime, 0, sizeof(*wtime));

	if (eft->second >= 60)
		return false;
	wtime->tm_sec  = eft->second;

	if (eft->minute >= 60)
		return false;
	wtime->tm_min  = eft->minute;

	if (eft->hour >= 24)
		return false;
	wtime->tm_hour = eft->hour;

	if (!eft->day || eft->day > 31)
		return false;
	wtime->tm_mday = eft->day;

	if (!eft->month || eft->month > 12)
		return false;
	wtime->tm_mon  = eft->month - 1;

	if (eft->year < 1900 || eft->year > 9999)
		return false;
	wtime->tm_year = eft->year - 1900;

	/* day in the year [1-365]*/
	wtime->tm_yday = compute_yday(eft);

	/* day of the week [0-6], Sunday=0 */
	wtime->tm_wday = compute_wday(eft, wtime->tm_yday);

	switch (eft->daylight & EFI_ISDST) {
	case EFI_ISDST:
		wtime->tm_isdst = 1;
		break;
	case EFI_TIME_ADJUST_DAYLIGHT:
		wtime->tm_isdst = 0;
		break;
	default:
		wtime->tm_isdst = -1;
	}

	return true;
}