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
typedef  int u16 ;
struct s5c73m3 {int dummy; } ;

/* Variables and functions */
 int REG_STATUS ; 
 int /*<<< orphan*/  REG_STATUS_ISP_COMMAND_COMPLETED ; 
 int s5c73m3_check_status (struct s5c73m3*,int /*<<< orphan*/ ) ; 
 int s5c73m3_write (struct s5c73m3*,int,int) ; 

int s5c73m3_isp_command(struct s5c73m3 *state, u16 command, u16 data)
{
	int ret;

	ret = s5c73m3_check_status(state, REG_STATUS_ISP_COMMAND_COMPLETED);
	if (ret < 0)
		return ret;

	ret = s5c73m3_write(state, 0x00095000, command);
	if (ret < 0)
		return ret;

	ret = s5c73m3_write(state, 0x00095002, data);
	if (ret < 0)
		return ret;

	return s5c73m3_write(state, REG_STATUS, 0x0001);
}