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
struct exynos_media_pipeline {int /*<<< orphan*/ * ops; } ;
struct fimc_pipeline {struct exynos_media_pipeline ep; int /*<<< orphan*/  list; } ;
struct fimc_md {int /*<<< orphan*/  pipelines; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  fimc_pipeline_ops ; 
 struct fimc_pipeline* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct exynos_media_pipeline *fimc_md_pipeline_create(
						struct fimc_md *fmd)
{
	struct fimc_pipeline *p;

	p = kzalloc(sizeof(*p), GFP_KERNEL);
	if (!p)
		return NULL;

	list_add_tail(&p->list, &fmd->pipelines);

	p->ep.ops = &fimc_pipeline_ops;
	return &p->ep;
}