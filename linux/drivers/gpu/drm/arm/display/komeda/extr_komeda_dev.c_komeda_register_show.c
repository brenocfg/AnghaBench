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
struct seq_file {struct komeda_dev* private; } ;
struct komeda_dev {int n_pipelines; int /*<<< orphan*/ * pipelines; TYPE_1__* funcs; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* dump_register ) (struct komeda_dev*,struct seq_file*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  komeda_pipeline_dump_register (int /*<<< orphan*/ ,struct seq_file*) ; 
 int /*<<< orphan*/  stub1 (struct komeda_dev*,struct seq_file*) ; 

__attribute__((used)) static int komeda_register_show(struct seq_file *sf, void *x)
{
	struct komeda_dev *mdev = sf->private;
	int i;

	if (mdev->funcs->dump_register)
		mdev->funcs->dump_register(mdev, sf);

	for (i = 0; i < mdev->n_pipelines; i++)
		komeda_pipeline_dump_register(mdev->pipelines[i], sf);

	return 0;
}