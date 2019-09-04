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
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dump_work; struct device* dev; int /*<<< orphan*/  reg_base_list; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _dpu_dump_work ; 
 TYPE_1__ dpu_dbg_base ; 
 int /*<<< orphan*/  pr_err (char*) ; 

int dpu_dbg_init(struct device *dev)
{
	if (!dev) {
		pr_err("invalid params\n");
		return -EINVAL;
	}

	INIT_LIST_HEAD(&dpu_dbg_base.reg_base_list);
	dpu_dbg_base.dev = dev;

	INIT_WORK(&dpu_dbg_base.dump_work, _dpu_dump_work);

	return 0;
}