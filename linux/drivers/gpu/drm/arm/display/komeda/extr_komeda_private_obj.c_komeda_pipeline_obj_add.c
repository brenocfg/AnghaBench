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
struct komeda_pipeline_state {int /*<<< orphan*/  obj; struct komeda_pipeline* pipe; } ;
struct komeda_pipeline {int /*<<< orphan*/  obj; } ;
struct komeda_kms_dev {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  drm_atomic_private_obj_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  komeda_pipeline_obj_funcs ; 
 struct komeda_pipeline_state* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int komeda_pipeline_obj_add(struct komeda_kms_dev *kms,
				   struct komeda_pipeline *pipe)
{
	struct komeda_pipeline_state *st;

	st = kzalloc(sizeof(*st), GFP_KERNEL);
	if (!st)
		return -ENOMEM;

	st->pipe = pipe;
	drm_atomic_private_obj_init(&kms->base, &pipe->obj, &st->obj,
				    &komeda_pipeline_obj_funcs);

	return 0;
}