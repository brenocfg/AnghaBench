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
struct TYPE_2__ {scalar_t__ next_bin; } ;
struct bnx2x_pending_mcast_cmd {int done; TYPE_1__ data; } ;
struct bnx2x_mcast_obj {scalar_t__ (* hdl_restore ) (struct bnx2x*,struct bnx2x_mcast_obj*,scalar_t__,int*) ;} ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 scalar_t__ stub1 (struct bnx2x*,struct bnx2x_mcast_obj*,scalar_t__,int*) ; 

__attribute__((used)) static inline void bnx2x_mcast_hdl_pending_restore_e2(struct bnx2x *bp,
	struct bnx2x_mcast_obj *o, struct bnx2x_pending_mcast_cmd *cmd_pos,
	int *line_idx)
{
	cmd_pos->data.next_bin = o->hdl_restore(bp, o, cmd_pos->data.next_bin,
						line_idx);

	if (cmd_pos->data.next_bin < 0)
		/* If o->set_restore returned -1 we are done */
		cmd_pos->done = true;
	else
		/* Start from the next bin next time */
		cmd_pos->data.next_bin++;
}