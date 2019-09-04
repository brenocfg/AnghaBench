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
typedef  void* u8 ;
struct TYPE_2__ {void** block_data; } ;
struct cpia2_command {int reg_count; void* start; TYPE_1__ buffer; } ;
struct camera_data {int dummy; } ;

/* Variables and functions */
 int cpia2_send_command (struct camera_data*,struct cpia2_command*) ; 

__attribute__((used)) static int cpia2_send_onebyte_command(struct camera_data *cam,
				      struct cpia2_command *cmd,
				      u8 start, u8 datum)
{
	cmd->buffer.block_data[0] = datum;
	cmd->start = start;
	cmd->reg_count = 1;
	return cpia2_send_command(cam, cmd);
}