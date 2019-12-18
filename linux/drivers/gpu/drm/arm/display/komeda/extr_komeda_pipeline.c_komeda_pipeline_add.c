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
struct komeda_pipeline_funcs {int dummy; } ;
struct komeda_pipeline {int id; struct komeda_pipeline_funcs const* funcs; struct komeda_dev* mdev; } ;
struct komeda_dev {int n_pipelines; struct komeda_pipeline** pipelines; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,...) ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  ENOSPC ; 
 struct komeda_pipeline* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int KOMEDA_MAX_PIPELINES ; 
 struct komeda_pipeline* devm_kzalloc (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 

struct komeda_pipeline *
komeda_pipeline_add(struct komeda_dev *mdev, size_t size,
		    const struct komeda_pipeline_funcs *funcs)
{
	struct komeda_pipeline *pipe;

	if (mdev->n_pipelines + 1 > KOMEDA_MAX_PIPELINES) {
		DRM_ERROR("Exceed max support %d pipelines.\n",
			  KOMEDA_MAX_PIPELINES);
		return ERR_PTR(-ENOSPC);
	}

	if (size < sizeof(*pipe)) {
		DRM_ERROR("Request pipeline size too small.\n");
		return ERR_PTR(-EINVAL);
	}

	pipe = devm_kzalloc(mdev->dev, size, GFP_KERNEL);
	if (!pipe)
		return ERR_PTR(-ENOMEM);

	pipe->mdev = mdev;
	pipe->id   = mdev->n_pipelines;
	pipe->funcs = funcs;

	mdev->pipelines[mdev->n_pipelines] = pipe;
	mdev->n_pipelines++;

	return pipe;
}