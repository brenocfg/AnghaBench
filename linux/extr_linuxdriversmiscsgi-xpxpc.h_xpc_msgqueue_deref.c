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
struct xpc_channel {size_t partid; int /*<<< orphan*/  references; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DBUG_ON (int) ; 
 scalar_t__ atomic_dec_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xpc_partitions ; 
 int /*<<< orphan*/  xpc_wakeup_channel_mgr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
xpc_msgqueue_deref(struct xpc_channel *ch)
{
	s32 refs = atomic_dec_return(&ch->references);

	DBUG_ON(refs < 0);
	if (refs == 0)
		xpc_wakeup_channel_mgr(&xpc_partitions[ch->partid]);
}