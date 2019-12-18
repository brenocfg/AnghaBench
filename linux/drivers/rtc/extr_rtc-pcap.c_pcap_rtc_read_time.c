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
typedef  unsigned long u32 ;
struct rtc_time {int dummy; } ;
struct pcap_rtc {int /*<<< orphan*/  pcap; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCAP_REG_RTC_DAY ; 
 int /*<<< orphan*/  PCAP_REG_RTC_TOD ; 
 unsigned long PCAP_RTC_DAY_MASK ; 
 unsigned long PCAP_RTC_TOD_MASK ; 
 unsigned long SEC_PER_DAY ; 
 struct pcap_rtc* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  ezx_pcap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  rtc_time64_to_tm (unsigned long,struct rtc_time*) ; 

__attribute__((used)) static int pcap_rtc_read_time(struct device *dev, struct rtc_time *tm)
{
	struct pcap_rtc *pcap_rtc = dev_get_drvdata(dev);
	unsigned long secs;
	u32 tod, days;

	ezx_pcap_read(pcap_rtc->pcap, PCAP_REG_RTC_TOD, &tod);
	secs = tod & PCAP_RTC_TOD_MASK;

	ezx_pcap_read(pcap_rtc->pcap, PCAP_REG_RTC_DAY, &days);
	secs += (days & PCAP_RTC_DAY_MASK) * SEC_PER_DAY;

	rtc_time64_to_tm(secs, tm);

	return 0;
}