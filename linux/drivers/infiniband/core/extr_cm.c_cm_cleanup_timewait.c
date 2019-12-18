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
struct cm_timewait_info {scalar_t__ inserted_remote_qp; int /*<<< orphan*/  remote_qp_node; scalar_t__ inserted_remote_id; int /*<<< orphan*/  remote_id_node; } ;
struct TYPE_2__ {int /*<<< orphan*/  remote_qp_table; int /*<<< orphan*/  remote_id_table; } ;

/* Variables and functions */
 TYPE_1__ cm ; 
 int /*<<< orphan*/  rb_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cm_cleanup_timewait(struct cm_timewait_info *timewait_info)
{
	if (timewait_info->inserted_remote_id) {
		rb_erase(&timewait_info->remote_id_node, &cm.remote_id_table);
		timewait_info->inserted_remote_id = 0;
	}

	if (timewait_info->inserted_remote_qp) {
		rb_erase(&timewait_info->remote_qp_node, &cm.remote_qp_table);
		timewait_info->inserted_remote_qp = 0;
	}
}