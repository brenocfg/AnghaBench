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
typedef  int u8 ;
struct rtc_time {int tm_sec; int tm_min; int tm_hour; int tm_wday; int tm_mday; int tm_mon; int tm_year; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  data ;

/* Variables and functions */
 int MCP795_LP_BIT ; 
 int /*<<< orphan*/  MCP795_REG_MONTH ; 
 int /*<<< orphan*/  MCP795_REG_SECONDS ; 
 int bin2bcd (int) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,struct rtc_time*) ; 
 int mcp795_rtcc_read (struct device*,int /*<<< orphan*/ ,int*,int) ; 
 int mcp795_rtcc_write (struct device*,int /*<<< orphan*/ ,int*,int) ; 
 int mcp795_start_oscillator (struct device*,int*) ; 
 int mcp795_stop_oscillator (struct device*,int*) ; 

__attribute__((used)) static int mcp795_set_time(struct device *dev, struct rtc_time *tim)
{
	int ret;
	u8 data[7];
	bool extosc;

	/* Stop RTC and store current value of EXTOSC bit */
	ret = mcp795_stop_oscillator(dev, &extosc);
	if (ret)
		return ret;

	/* Read first, so we can leave config bits untouched */
	ret = mcp795_rtcc_read(dev, MCP795_REG_SECONDS, data, sizeof(data));

	if (ret)
		return ret;

	data[0] = (data[0] & 0x80) | bin2bcd(tim->tm_sec);
	data[1] = (data[1] & 0x80) | bin2bcd(tim->tm_min);
	data[2] = bin2bcd(tim->tm_hour);
	data[3] = (data[3] & 0xF8) | bin2bcd(tim->tm_wday + 1);
	data[4] = bin2bcd(tim->tm_mday);
	data[5] = (data[5] & MCP795_LP_BIT) | bin2bcd(tim->tm_mon + 1);

	if (tim->tm_year > 100)
		tim->tm_year -= 100;

	data[6] = bin2bcd(tim->tm_year);

	/* Always write the date and month using a separate Write command.
	 * This is a workaround for a know silicon issue that some combinations
	 * of date and month values may result in the date being reset to 1.
	 */
	ret = mcp795_rtcc_write(dev, MCP795_REG_SECONDS, data, 5);
	if (ret)
		return ret;

	ret = mcp795_rtcc_write(dev, MCP795_REG_MONTH, &data[5], 2);
	if (ret)
		return ret;

	/* Start back RTC and restore previous value of EXTOSC bit.
	 * There is no need to clear EXTOSC bit when the previous value was 0
	 * because it was already cleared when stopping the RTC oscillator.
	 */
	ret = mcp795_start_oscillator(dev, extosc ? &extosc : NULL);
	if (ret)
		return ret;

	dev_dbg(dev, "Set mcp795: %ptR\n", tim);

	return 0;
}