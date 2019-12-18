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
typedef  int /*<<< orphan*/  u32 ;
struct slim_val_inf {size_t num_bytes; int /*<<< orphan*/ * comp; int /*<<< orphan*/ * wbuf; int /*<<< orphan*/ * rbuf; int /*<<< orphan*/  start_offset; } ;

/* Variables and functions */

__attribute__((used)) static void slim_fill_msg(struct slim_val_inf *msg, u32 addr,
			 size_t count, u8 *rbuf, u8 *wbuf)
{
	msg->start_offset = addr;
	msg->num_bytes = count;
	msg->rbuf = rbuf;
	msg->wbuf = wbuf;
	msg->comp = NULL;
}