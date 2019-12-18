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
typedef  int u32 ;
struct ipw_priv {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  IPW_ORD_STAT_RTC ; 
 struct ipw_priv* dev_get_drvdata (struct device*) ; 
 scalar_t__ ipw_get_ordinal (struct ipw_priv*,int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t show_rtc(struct device *d, struct device_attribute *attr,
			char *buf)
{
	u32 len = sizeof(u32), tmp = 0;
	struct ipw_priv *p = dev_get_drvdata(d);

	if (ipw_get_ordinal(p, IPW_ORD_STAT_RTC, &tmp, &len))
		return 0;

	return sprintf(buf, "0x%08x\n", tmp);
}