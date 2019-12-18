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
struct TYPE_3__ {int /*<<< orphan*/  obj; } ;
struct komeda_timing_ctrlr {TYPE_1__ base; } ;
struct komeda_kms_dev {int /*<<< orphan*/  base; } ;
struct TYPE_4__ {int /*<<< orphan*/  obj; TYPE_1__* component; } ;
struct komeda_compiz_state {TYPE_2__ base; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  drm_atomic_private_obj_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  komeda_timing_ctrlr_obj_funcs ; 
 struct komeda_compiz_state* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int komeda_timing_ctrlr_obj_add(struct komeda_kms_dev *kms,
				       struct komeda_timing_ctrlr *ctrlr)
{
	struct komeda_compiz_state *st;

	st = kzalloc(sizeof(*st), GFP_KERNEL);
	if (!st)
		return -ENOMEM;

	st->base.component = &ctrlr->base;
	drm_atomic_private_obj_init(&kms->base, &ctrlr->base.obj, &st->base.obj,
				    &komeda_timing_ctrlr_obj_funcs);

	return 0;
}