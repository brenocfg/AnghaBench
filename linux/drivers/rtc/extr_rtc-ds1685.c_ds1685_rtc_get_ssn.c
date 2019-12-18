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
struct ds1685_priv {int /*<<< orphan*/  (* read ) (struct ds1685_priv*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  RTC_BANK1_SSN_BYTE_1 ; 
 int /*<<< orphan*/  RTC_BANK1_SSN_BYTE_2 ; 
 int /*<<< orphan*/  RTC_BANK1_SSN_BYTE_3 ; 
 int /*<<< orphan*/  RTC_BANK1_SSN_BYTE_4 ; 
 int /*<<< orphan*/  RTC_BANK1_SSN_BYTE_5 ; 
 int /*<<< orphan*/  RTC_BANK1_SSN_BYTE_6 ; 
 int /*<<< orphan*/  RTC_BANK1_SSN_CRC ; 
 int /*<<< orphan*/  RTC_BANK1_SSN_MODEL ; 
 int /*<<< orphan*/  stub1 (struct ds1685_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct ds1685_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct ds1685_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (struct ds1685_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (struct ds1685_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub6 (struct ds1685_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub7 (struct ds1685_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub8 (struct ds1685_priv*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
ds1685_rtc_get_ssn(struct ds1685_priv *rtc, u8 *ssn)
{
	ssn[0] = rtc->read(rtc, RTC_BANK1_SSN_MODEL);
	ssn[1] = rtc->read(rtc, RTC_BANK1_SSN_BYTE_1);
	ssn[2] = rtc->read(rtc, RTC_BANK1_SSN_BYTE_2);
	ssn[3] = rtc->read(rtc, RTC_BANK1_SSN_BYTE_3);
	ssn[4] = rtc->read(rtc, RTC_BANK1_SSN_BYTE_4);
	ssn[5] = rtc->read(rtc, RTC_BANK1_SSN_BYTE_5);
	ssn[6] = rtc->read(rtc, RTC_BANK1_SSN_BYTE_6);
	ssn[7] = rtc->read(rtc, RTC_BANK1_SSN_CRC);
}