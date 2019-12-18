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
struct vc4_dev {scalar_t__ emit_seqno; scalar_t__ finished_seqno; scalar_t__ hang_state; TYPE_2__* bin_bo; } ;
struct drm_device {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  base; } ;
struct TYPE_4__ {TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  drm_gem_object_put_unlocked (int /*<<< orphan*/ *) ; 
 struct vc4_dev* to_vc4_dev (struct drm_device*) ; 
 int /*<<< orphan*/  vc4_free_hang_state (struct drm_device*,scalar_t__) ; 

void
vc4_gem_destroy(struct drm_device *dev)
{
	struct vc4_dev *vc4 = to_vc4_dev(dev);

	/* Waiting for exec to finish would need to be done before
	 * unregistering V3D.
	 */
	WARN_ON(vc4->emit_seqno != vc4->finished_seqno);

	/* V3D should already have disabled its interrupt and cleared
	 * the overflow allocation registers.  Now free the object.
	 */
	if (vc4->bin_bo) {
		drm_gem_object_put_unlocked(&vc4->bin_bo->base.base);
		vc4->bin_bo = NULL;
	}

	if (vc4->hang_state)
		vc4_free_hang_state(dev, vc4->hang_state);
}