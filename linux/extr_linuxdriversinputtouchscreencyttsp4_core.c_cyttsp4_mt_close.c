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
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct input_dev {TYPE_1__ dev; } ;
struct cyttsp4_mt_data {int /*<<< orphan*/  report_lock; int /*<<< orphan*/  is_suspended; } ;

/* Variables and functions */
 struct cyttsp4_mt_data* input_get_drvdata (struct input_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cyttsp4_mt_close(struct input_dev *input)
{
	struct cyttsp4_mt_data *md = input_get_drvdata(input);
	mutex_lock(&md->report_lock);
	if (!md->is_suspended)
		pm_runtime_put(input->dev.parent);
	mutex_unlock(&md->report_lock);
}