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
struct tg3 {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  OTP_CTRL ; 
 int OTP_CTRL_OTP_CMD_START ; 
 int /*<<< orphan*/  OTP_STATUS ; 
 int OTP_STATUS_CMD_DONE ; 
 int tr32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tw32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int tg3_issue_otp_command(struct tg3 *tp, u32 cmd)
{
	int i;
	u32 val;

	tw32(OTP_CTRL, cmd | OTP_CTRL_OTP_CMD_START);
	tw32(OTP_CTRL, cmd);

	/* Wait for up to 1 ms for command to execute. */
	for (i = 0; i < 100; i++) {
		val = tr32(OTP_STATUS);
		if (val & OTP_STATUS_CMD_DONE)
			break;
		udelay(10);
	}

	return (val & OTP_STATUS_CMD_DONE) ? 0 : -EBUSY;
}