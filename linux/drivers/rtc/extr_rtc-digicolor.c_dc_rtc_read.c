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
typedef  unsigned long u32 ;
struct dc_rtc {scalar_t__ regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/  const*) ; 
#define  CMD_NOP 129 
#define  CMD_READ 128 
 scalar_t__ DC_RTC_REFERENCE ; 
 scalar_t__ DC_RTC_TIME ; 
 int dc_rtc_cmds (struct dc_rtc*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 unsigned long readl_relaxed (scalar_t__) ; 

__attribute__((used)) static int dc_rtc_read(struct dc_rtc *rtc, unsigned long *val)
{
	static const u8 read_cmds[] = {CMD_READ, CMD_NOP};
	u32 reference, time1, time2;
	int ret;

	ret = dc_rtc_cmds(rtc, read_cmds, ARRAY_SIZE(read_cmds));
	if (ret < 0)
		return ret;

	reference = readl_relaxed(rtc->regs + DC_RTC_REFERENCE);
	time1 = readl_relaxed(rtc->regs + DC_RTC_TIME);
	/* Read twice to ensure consistency */
	while (1) {
		time2 = readl_relaxed(rtc->regs + DC_RTC_TIME);
		if (time1 == time2)
			break;
		time1 = time2;
	}

	*val = reference + time1;
	return 0;
}