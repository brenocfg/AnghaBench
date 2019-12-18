#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int ;
struct TYPE_2__ {scalar_t__ port_tts; } ;

/* Variables and functions */
 int CMD_control ; 
 int CMD_null ; 
 int STAT_cmd_ready ; 
 int dt_getstatus () ; 
 int /*<<< orphan*/  dt_sendcmd (int) ; 
 int /*<<< orphan*/  dt_waitbit (int) ; 
 int /*<<< orphan*/  outb_p (int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_1__ speakup_info ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int dt_ctrl(u_int cmd)
{
	int timeout = 10;

	if (!dt_waitbit(STAT_cmd_ready))
		return -1;
	outb_p(0, speakup_info.port_tts + 2);
	outb_p(0, speakup_info.port_tts + 3);
	dt_getstatus();
	dt_sendcmd(CMD_control | cmd);
	outb_p(0, speakup_info.port_tts + 6);
	while (dt_getstatus() & STAT_cmd_ready) {
		udelay(20);
		if (--timeout == 0)
			break;
	}
	dt_sendcmd(CMD_null);
	return 0;
}