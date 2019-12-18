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
struct vmw_stdu_update {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  unit; } ;
struct vmw_screen_target_display_unit {int /*<<< orphan*/  display_height; int /*<<< orphan*/  display_width; TYPE_1__ base; int /*<<< orphan*/  defined; } ;
struct vmw_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int EINVAL ; 
 int ENOMEM ; 
 struct vmw_stdu_update* VMW_FIFO_RESERVE (struct vmw_private*,int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmw_fifo_commit (struct vmw_private*,int) ; 
 int /*<<< orphan*/  vmw_stdu_populate_update (struct vmw_stdu_update*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vmw_stdu_update_st(struct vmw_private *dev_priv,
			      struct vmw_screen_target_display_unit *stdu)
{
	struct vmw_stdu_update *cmd;

	if (!stdu->defined) {
		DRM_ERROR("No screen target defined");
		return -EINVAL;
	}

	cmd = VMW_FIFO_RESERVE(dev_priv, sizeof(*cmd));
	if (unlikely(cmd == NULL))
		return -ENOMEM;

	vmw_stdu_populate_update(cmd, stdu->base.unit,
				 0, stdu->display_width,
				 0, stdu->display_height);

	vmw_fifo_commit(dev_priv, sizeof(*cmd));

	return 0;
}