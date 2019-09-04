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
struct TYPE_3__ {unsigned long remote_msgqueue_pa; } ;
struct TYPE_4__ {TYPE_1__ sn2; } ;
struct xpc_channel {TYPE_2__ sn; } ;
typedef  enum xp_retval { ____Placeholder_xp_retval } xp_retval ;

/* Variables and functions */
 int xpSuccess ; 

__attribute__((used)) static enum xp_retval
xpc_save_remote_msgqueue_pa_sn2(struct xpc_channel *ch,
				unsigned long msgqueue_pa)
{
	ch->sn.sn2.remote_msgqueue_pa = msgqueue_pa;
	return xpSuccess;
}