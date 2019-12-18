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
struct TYPE_3__ {int /*<<< orphan*/  event; } ;
struct TYPE_4__ {TYPE_1__ cm_event; int /*<<< orphan*/  work; int /*<<< orphan*/  local_id; } ;
struct cm_timewait_info {TYPE_2__ work; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct cm_timewait_info* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IB_CM_TIMEWAIT_EXIT ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cm_work_handler ; 
 struct cm_timewait_info* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct cm_timewait_info * cm_create_timewait_info(__be32 local_id)
{
	struct cm_timewait_info *timewait_info;

	timewait_info = kzalloc(sizeof *timewait_info, GFP_KERNEL);
	if (!timewait_info)
		return ERR_PTR(-ENOMEM);

	timewait_info->work.local_id = local_id;
	INIT_DELAYED_WORK(&timewait_info->work.work, cm_work_handler);
	timewait_info->work.cm_event.event = IB_CM_TIMEWAIT_EXIT;
	return timewait_info;
}