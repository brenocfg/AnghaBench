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
typedef  int uint32_t ;
struct vmw_stdu_update {int dummy; } ;
struct vmw_du_update_plane {TYPE_1__* du; } ;
struct drm_rect {int /*<<< orphan*/  y2; int /*<<< orphan*/  y1; int /*<<< orphan*/  x2; int /*<<< orphan*/  x1; } ;
struct TYPE_2__ {int /*<<< orphan*/  unit; } ;

/* Variables and functions */
 int /*<<< orphan*/  vmw_stdu_populate_update (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32_t
vmw_stdu_surface_populate_update(struct vmw_du_update_plane  *update, void *cmd,
				 struct drm_rect *bb)
{
	vmw_stdu_populate_update(cmd, update->du->unit, bb->x1, bb->x2, bb->y1,
				 bb->y2);

	return sizeof(struct vmw_stdu_update);
}