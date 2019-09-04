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
typedef  int /*<<< orphan*/  MGSLPC_INFO ;

/* Variables and functions */
 scalar_t__ CMDR ; 
 int /*<<< orphan*/  wait_command_complete (int /*<<< orphan*/ *,unsigned char) ; 
 int /*<<< orphan*/  write_reg (int /*<<< orphan*/ *,unsigned char,unsigned char) ; 

__attribute__((used)) static void issue_command(MGSLPC_INFO *info, unsigned char channel, unsigned char cmd)
{
	wait_command_complete(info, channel);
	write_reg(info, (unsigned char) (channel + CMDR), cmd);
}