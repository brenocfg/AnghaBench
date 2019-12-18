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
typedef  int /*<<< orphan*/  u32 ;
struct rtc_time {int dummy; } ;
struct pxa_rtc {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RDCR ; 
 int /*<<< orphan*/  RYCR ; 
 struct pxa_rtc* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  rtc_readl (struct pxa_rtc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tm_calc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct rtc_time*) ; 

__attribute__((used)) static int pxa_rtc_read_time(struct device *dev, struct rtc_time *tm)
{
	struct pxa_rtc *pxa_rtc = dev_get_drvdata(dev);
	u32 rycr, rdcr;

	rycr = rtc_readl(pxa_rtc, RYCR);
	rdcr = rtc_readl(pxa_rtc, RDCR);

	tm_calc(rycr, rdcr, tm);
	return 0;
}