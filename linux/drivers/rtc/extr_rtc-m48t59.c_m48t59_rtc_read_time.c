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
struct rtc_time {int tm_year; void* tm_sec; void* tm_min; void* tm_hour; void* tm_wday; void* tm_mday; scalar_t__ tm_mon; } ;
struct m48t59_private {int /*<<< orphan*/  lock; } ;
struct m48t59_plat_data {scalar_t__ type; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ M48T59RTC_TYPE_M48T59 ; 
 int /*<<< orphan*/  M48T59_CLEAR_BITS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M48T59_CNTL ; 
 int /*<<< orphan*/  M48T59_CNTL_READ ; 
 int /*<<< orphan*/  M48T59_HOUR ; 
 int /*<<< orphan*/  M48T59_MDAY ; 
 int /*<<< orphan*/  M48T59_MIN ; 
 int /*<<< orphan*/  M48T59_MONTH ; 
 int M48T59_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M48T59_SEC ; 
 int /*<<< orphan*/  M48T59_SET_BITS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M48T59_WDAY ; 
 int M48T59_WDAY_CB ; 
 int M48T59_WDAY_CEB ; 
 int /*<<< orphan*/  M48T59_YEAR ; 
 void* bcd2bin (int) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,...) ; 
 struct m48t59_private* dev_get_drvdata (struct device*) ; 
 struct m48t59_plat_data* dev_get_platdata (struct device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int m48t59_rtc_read_time(struct device *dev, struct rtc_time *tm)
{
	struct m48t59_plat_data *pdata = dev_get_platdata(dev);
	struct m48t59_private *m48t59 = dev_get_drvdata(dev);
	unsigned long flags;
	u8 val;

	spin_lock_irqsave(&m48t59->lock, flags);
	/* Issue the READ command */
	M48T59_SET_BITS(M48T59_CNTL_READ, M48T59_CNTL);

	tm->tm_year	= bcd2bin(M48T59_READ(M48T59_YEAR));
	/* tm_mon is 0-11 */
	tm->tm_mon	= bcd2bin(M48T59_READ(M48T59_MONTH)) - 1;
	tm->tm_mday	= bcd2bin(M48T59_READ(M48T59_MDAY));

	val = M48T59_READ(M48T59_WDAY);
	if ((pdata->type == M48T59RTC_TYPE_M48T59) &&
	    (val & M48T59_WDAY_CEB) && (val & M48T59_WDAY_CB)) {
		dev_dbg(dev, "Century bit is enabled\n");
		tm->tm_year += 100;	/* one century */
	}
#ifdef CONFIG_SPARC
	/* Sun SPARC machines count years since 1968 */
	tm->tm_year += 68;
#endif

	tm->tm_wday	= bcd2bin(val & 0x07);
	tm->tm_hour	= bcd2bin(M48T59_READ(M48T59_HOUR) & 0x3F);
	tm->tm_min	= bcd2bin(M48T59_READ(M48T59_MIN) & 0x7F);
	tm->tm_sec	= bcd2bin(M48T59_READ(M48T59_SEC) & 0x7F);

	/* Clear the READ bit */
	M48T59_CLEAR_BITS(M48T59_CNTL_READ, M48T59_CNTL);
	spin_unlock_irqrestore(&m48t59->lock, flags);

	dev_dbg(dev, "RTC read time %ptR\n", tm);
	return 0;
}