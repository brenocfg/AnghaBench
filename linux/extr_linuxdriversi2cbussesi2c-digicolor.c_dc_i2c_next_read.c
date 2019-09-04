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
struct dc_i2c {scalar_t__ msgbuf_ptr; TYPE_1__* msg; } ;
struct TYPE_2__ {scalar_t__ len; } ;

/* Variables and functions */
 int /*<<< orphan*/  II_CMD_GET_ACK ; 
 int /*<<< orphan*/  II_CMD_GET_NOACK ; 
 int /*<<< orphan*/  dc_i2c_cmd (struct dc_i2c*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dc_i2c_next_read(struct dc_i2c *i2c)
{
	bool last = (i2c->msgbuf_ptr + 1 == i2c->msg->len);

	dc_i2c_cmd(i2c, last ? II_CMD_GET_NOACK : II_CMD_GET_ACK);
}