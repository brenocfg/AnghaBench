#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct qxl_release {int dummy; } ;
struct qxl_rect {int dummy; } ;
struct TYPE_9__ {scalar_t__ y; scalar_t__ x; } ;
struct TYPE_10__ {scalar_t__ bitmap; TYPE_3__ pos; scalar_t__ flags; } ;
struct TYPE_7__ {int /*<<< orphan*/  color; } ;
struct TYPE_8__ {TYPE_1__ u; int /*<<< orphan*/  type; } ;
struct TYPE_11__ {TYPE_4__ mask; int /*<<< orphan*/  rop_descriptor; TYPE_2__ brush; } ;
struct TYPE_12__ {TYPE_5__ fill; } ;
struct qxl_drawable {int /*<<< orphan*/  release_info; TYPE_6__ u; } ;
struct qxl_draw_fill {int /*<<< orphan*/  rop; int /*<<< orphan*/  color; struct qxl_rect rect; struct qxl_device* qdev; } ;
struct qxl_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  QXL_CMD_DRAW ; 
 int /*<<< orphan*/  QXL_DRAW_FILL ; 
 int /*<<< orphan*/  SPICE_BRUSH_TYPE_SOLID ; 
 int alloc_drawable (struct qxl_device*,struct qxl_release**) ; 
 int /*<<< orphan*/  free_drawable (struct qxl_device*,struct qxl_release*) ; 
 int make_drawable (struct qxl_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct qxl_rect*,struct qxl_release*) ; 
 int /*<<< orphan*/  qxl_push_command_ring_release (struct qxl_device*,struct qxl_release*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qxl_release_backoff_reserve_list (struct qxl_release*) ; 
 int /*<<< orphan*/  qxl_release_fence_buffer_objects (struct qxl_release*) ; 
 scalar_t__ qxl_release_map (struct qxl_device*,struct qxl_release*) ; 
 int qxl_release_reserve_list (struct qxl_release*,int) ; 
 int /*<<< orphan*/  qxl_release_unmap (struct qxl_device*,struct qxl_release*,int /*<<< orphan*/ *) ; 

void qxl_draw_fill(struct qxl_draw_fill *qxl_draw_fill_rec)
{
	struct qxl_device *qdev = qxl_draw_fill_rec->qdev;
	struct qxl_rect rect = qxl_draw_fill_rec->rect;
	uint32_t color = qxl_draw_fill_rec->color;
	uint16_t rop = qxl_draw_fill_rec->rop;
	struct qxl_drawable *drawable;
	struct qxl_release *release;
	int ret;

	ret = alloc_drawable(qdev, &release);
	if (ret)
		return;

	/* do a reservation run over all the objects we just allocated */
	ret = qxl_release_reserve_list(release, true);
	if (ret)
		goto out_free_release;

	ret = make_drawable(qdev, 0, QXL_DRAW_FILL, &rect, release);
	if (ret) {
		qxl_release_backoff_reserve_list(release);
		goto out_free_release;
	}

	drawable = (struct qxl_drawable *)qxl_release_map(qdev, release);
	drawable->u.fill.brush.type = SPICE_BRUSH_TYPE_SOLID;
	drawable->u.fill.brush.u.color = color;
	drawable->u.fill.rop_descriptor = rop;
	drawable->u.fill.mask.flags = 0;
	drawable->u.fill.mask.pos.x = 0;
	drawable->u.fill.mask.pos.y = 0;
	drawable->u.fill.mask.bitmap = 0;

	qxl_release_unmap(qdev, release, &drawable->release_info);

	qxl_push_command_ring_release(qdev, release, QXL_CMD_DRAW, false);
	qxl_release_fence_buffer_objects(release);

out_free_release:
	if (ret)
		free_drawable(qdev, release);
}