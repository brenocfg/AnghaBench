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
struct komeda_pipeline {int n_layers; int /*<<< orphan*/ * layers; } ;
struct komeda_kms_dev {int dummy; } ;
struct komeda_dev {int n_pipelines; struct komeda_pipeline** pipelines; } ;

/* Variables and functions */
 int komeda_plane_add (struct komeda_kms_dev*,int /*<<< orphan*/ ) ; 

int komeda_kms_add_planes(struct komeda_kms_dev *kms, struct komeda_dev *mdev)
{
	struct komeda_pipeline *pipe;
	int i, j, err;

	for (i = 0; i < mdev->n_pipelines; i++) {
		pipe = mdev->pipelines[i];

		for (j = 0; j < pipe->n_layers; j++) {
			err = komeda_plane_add(kms, pipe->layers[j]);
			if (err)
				return err;
		}
	}

	return 0;
}