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
struct pt3_board {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PT3_CMD_ADDR_INIT_TUNER ; 
 int send_i2c_cmd (struct pt3_board*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

int  pt3_init_all_mxl301rf(struct pt3_board *pt3)
{
	usleep_range(1000, 2000);
	return send_i2c_cmd(pt3, PT3_CMD_ADDR_INIT_TUNER);
}