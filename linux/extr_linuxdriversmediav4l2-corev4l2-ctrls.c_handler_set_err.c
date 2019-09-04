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
struct v4l2_ctrl_handler {int error; } ;

/* Variables and functions */

__attribute__((used)) static inline int handler_set_err(struct v4l2_ctrl_handler *hdl, int err)
{
	if (hdl->error == 0)
		hdl->error = err;
	return err;
}