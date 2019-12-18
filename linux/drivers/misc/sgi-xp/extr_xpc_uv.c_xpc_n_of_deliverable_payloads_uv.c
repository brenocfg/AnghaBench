#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  recv_msg_list; } ;
struct TYPE_4__ {TYPE_1__ uv; } ;
struct xpc_channel {TYPE_2__ sn; } ;

/* Variables and functions */
 int xpc_n_of_fifo_entries_uv (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
xpc_n_of_deliverable_payloads_uv(struct xpc_channel *ch)
{
	return xpc_n_of_fifo_entries_uv(&ch->sn.uv.recv_msg_list);
}