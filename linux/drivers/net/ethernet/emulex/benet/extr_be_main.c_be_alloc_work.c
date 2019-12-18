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
struct be_cmd_work {struct be_adapter* adapter; int /*<<< orphan*/  work; } ;
struct be_adapter {TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,void (*) (struct work_struct*)) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct be_cmd_work* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct be_cmd_work *be_alloc_work(struct be_adapter *adapter,
					 void (*func)(struct work_struct *))
{
	struct be_cmd_work *work;

	work = kzalloc(sizeof(*work), GFP_ATOMIC);
	if (!work) {
		dev_err(&adapter->pdev->dev,
			"be_work memory allocation failed\n");
		return NULL;
	}

	INIT_WORK(&work->work, func);
	work->adapter = adapter;
	return work;
}