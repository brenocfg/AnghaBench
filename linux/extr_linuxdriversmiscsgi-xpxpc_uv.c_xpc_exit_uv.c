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

/* Variables and functions */
 int /*<<< orphan*/  xpc_activate_mq_uv ; 
 int /*<<< orphan*/  xpc_destroy_gru_mq_uv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpc_notify_mq_uv ; 

void
xpc_exit_uv(void)
{
	xpc_destroy_gru_mq_uv(xpc_notify_mq_uv);
	xpc_destroy_gru_mq_uv(xpc_activate_mq_uv);
}