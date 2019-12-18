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
struct komeda_pipeline {int dummy; } ;
struct komeda_dev {int n_pipelines; struct komeda_pipeline** pipelines; } ;

/* Variables and functions */
 int /*<<< orphan*/  komeda_pipeline_assemble (struct komeda_pipeline*) ; 
 int /*<<< orphan*/  komeda_pipeline_dump (struct komeda_pipeline*) ; 

int komeda_assemble_pipelines(struct komeda_dev *mdev)
{
	struct komeda_pipeline *pipe;
	int i;

	for (i = 0; i < mdev->n_pipelines; i++) {
		pipe = mdev->pipelines[i];

		komeda_pipeline_assemble(pipe);
		komeda_pipeline_dump(pipe);
	}

	return 0;
}