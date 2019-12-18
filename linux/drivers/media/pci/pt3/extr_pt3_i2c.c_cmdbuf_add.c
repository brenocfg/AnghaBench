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
struct pt3_i2cbuf {int num_cmds; int tmp; int* data; } ;
typedef  enum ctl_cmd { ____Placeholder_ctl_cmd } ctl_cmd ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 

__attribute__((used)) static void cmdbuf_add(struct pt3_i2cbuf *cbuf, enum ctl_cmd cmd)
{
	int buf_idx;

	if ((cbuf->num_cmds % 2) == 0)
		cbuf->tmp = cmd;
	else {
		cbuf->tmp |= cmd << 4;
		buf_idx = cbuf->num_cmds / 2;
		if (buf_idx < ARRAY_SIZE(cbuf->data))
			cbuf->data[buf_idx] = cbuf->tmp;
	}
	cbuf->num_cmds++;
}