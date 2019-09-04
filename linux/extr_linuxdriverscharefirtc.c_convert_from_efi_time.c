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
struct rtc_time {int tm_isdst; int /*<<< orphan*/  tm_yday; int /*<<< orphan*/  tm_wday; scalar_t__ tm_year; scalar_t__ tm_mon; int /*<<< orphan*/  tm_mday; int /*<<< orphan*/  tm_hour; int /*<<< orphan*/  tm_min; int /*<<< orphan*/  tm_sec; } ;
struct TYPE_5__ {int daylight; scalar_t__ year; scalar_t__ month; int /*<<< orphan*/  day; int /*<<< orphan*/  hour; int /*<<< orphan*/  minute; int /*<<< orphan*/  second; } ;
typedef  TYPE_1__ efi_time_t ;

/* Variables and functions */
#define  EFI_ISDST 129 
#define  EFI_TIME_ADJUST_DAYLIGHT 128 
 int /*<<< orphan*/  compute_wday (TYPE_1__*) ; 
 int /*<<< orphan*/  compute_yday (TYPE_1__*) ; 
 int /*<<< orphan*/  memset (struct rtc_time*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
convert_from_efi_time(efi_time_t *eft, struct rtc_time *wtime)
{
	memset(wtime, 0, sizeof(*wtime));
	wtime->tm_sec  = eft->second;
	wtime->tm_min  = eft->minute;
	wtime->tm_hour = eft->hour;
	wtime->tm_mday = eft->day;
	wtime->tm_mon  = eft->month - 1;
	wtime->tm_year = eft->year - 1900;

	/* day of the week [0-6], Sunday=0 */
	wtime->tm_wday = compute_wday(eft);

	/* day in the year [1-365]*/
	wtime->tm_yday = compute_yday(eft);


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
}