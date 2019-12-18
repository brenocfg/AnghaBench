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
struct rtc_time {int tm_sec; int tm_min; int tm_hour; int tm_mday; int tm_mon; int tm_year; int tm_wday; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M48T86_B ; 
 unsigned char M48T86_B_DM ; 
 unsigned char M48T86_B_H24 ; 
 int /*<<< orphan*/  M48T86_DOM ; 
 int /*<<< orphan*/  M48T86_DOW ; 
 int /*<<< orphan*/  M48T86_HOUR ; 
 int /*<<< orphan*/  M48T86_MIN ; 
 int /*<<< orphan*/  M48T86_MONTH ; 
 int /*<<< orphan*/  M48T86_SEC ; 
 int /*<<< orphan*/  M48T86_YEAR ; 
 int bcd2bin (int) ; 
 int m48t86_readb (struct device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int m48t86_rtc_read_time(struct device *dev, struct rtc_time *tm)
{
	unsigned char reg;

	reg = m48t86_readb(dev, M48T86_B);

	if (reg & M48T86_B_DM) {
		/* data (binary) mode */
		tm->tm_sec	= m48t86_readb(dev, M48T86_SEC);
		tm->tm_min	= m48t86_readb(dev, M48T86_MIN);
		tm->tm_hour	= m48t86_readb(dev, M48T86_HOUR) & 0x3f;
		tm->tm_mday	= m48t86_readb(dev, M48T86_DOM);
		/* tm_mon is 0-11 */
		tm->tm_mon	= m48t86_readb(dev, M48T86_MONTH) - 1;
		tm->tm_year	= m48t86_readb(dev, M48T86_YEAR) + 100;
		tm->tm_wday	= m48t86_readb(dev, M48T86_DOW);
	} else {
		/* bcd mode */
		tm->tm_sec	= bcd2bin(m48t86_readb(dev, M48T86_SEC));
		tm->tm_min	= bcd2bin(m48t86_readb(dev, M48T86_MIN));
		tm->tm_hour	= bcd2bin(m48t86_readb(dev, M48T86_HOUR) &
					  0x3f);
		tm->tm_mday	= bcd2bin(m48t86_readb(dev, M48T86_DOM));
		/* tm_mon is 0-11 */
		tm->tm_mon	= bcd2bin(m48t86_readb(dev, M48T86_MONTH)) - 1;
		tm->tm_year	= bcd2bin(m48t86_readb(dev, M48T86_YEAR)) + 100;
		tm->tm_wday	= bcd2bin(m48t86_readb(dev, M48T86_DOW));
	}

	/* correct the hour if the clock is in 12h mode */
	if (!(reg & M48T86_B_H24))
		if (m48t86_readb(dev, M48T86_HOUR) & 0x80)
			tm->tm_hour += 12;

	return 0;
}