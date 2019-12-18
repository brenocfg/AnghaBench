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
struct TYPE_2__ {int /*<<< orphan*/  id; } ;
struct drm_encoder {TYPE_1__ base; } ;
struct dpu_rm {int /*<<< orphan*/  rm_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  _dpu_rm_release_reservation (struct dpu_rm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void dpu_rm_release(struct dpu_rm *rm, struct drm_encoder *enc)
{
	mutex_lock(&rm->rm_lock);

	_dpu_rm_release_reservation(rm, enc->base.id);

	mutex_unlock(&rm->rm_lock);
}