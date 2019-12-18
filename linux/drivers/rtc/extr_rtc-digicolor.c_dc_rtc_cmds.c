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
typedef  int const u8 ;
struct dc_rtc {scalar_t__ regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_DELAY_US ; 
 int /*<<< orphan*/  CMD_TIMEOUT_US ; 
 int const DC_RTC_CMD_MASK ; 
 scalar_t__ DC_RTC_CONTROL ; 
 int const DC_RTC_GO_BUSY ; 
 int readb_relaxed_poll_timeout (scalar_t__,int const,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writeb_relaxed (int const,scalar_t__) ; 

__attribute__((used)) static int dc_rtc_cmds(struct dc_rtc *rtc, const u8 *cmds, int len)
{
	u8 val;
	int i, ret;

	for (i = 0; i < len; i++) {
		writeb_relaxed((cmds[i] & DC_RTC_CMD_MASK) | DC_RTC_GO_BUSY,
			       rtc->regs + DC_RTC_CONTROL);
		ret = readb_relaxed_poll_timeout(
			rtc->regs + DC_RTC_CONTROL, val,
			!(val & DC_RTC_GO_BUSY), CMD_DELAY_US, CMD_TIMEOUT_US);
		if (ret < 0)
			return ret;
	}

	return 0;
}