#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ttm_mem_reg {int dummy; } ;
struct TYPE_8__ {scalar_t__ mem_type; } ;
struct ttm_buffer_object {TYPE_4__ mem; } ;
struct qxl_device {int dummy; } ;
struct TYPE_6__ {TYPE_1__* dev; } ;
struct TYPE_7__ {TYPE_2__ base; } ;
struct qxl_bo {scalar_t__ surface_id; TYPE_3__ tbo; } ;
struct TYPE_5__ {struct qxl_device* dev_private; } ;

/* Variables and functions */
 scalar_t__ TTM_PL_PRIV ; 
 int /*<<< orphan*/  qxl_surface_evict (struct qxl_device*,struct qxl_bo*,int) ; 
 int /*<<< orphan*/  qxl_ttm_bo_is_qxl_bo (struct ttm_buffer_object*) ; 
 struct qxl_bo* to_qxl_bo (struct ttm_buffer_object*) ; 

__attribute__((used)) static void qxl_bo_move_notify(struct ttm_buffer_object *bo,
			       bool evict,
			       struct ttm_mem_reg *new_mem)
{
	struct qxl_bo *qbo;
	struct qxl_device *qdev;

	if (!qxl_ttm_bo_is_qxl_bo(bo))
		return;
	qbo = to_qxl_bo(bo);
	qdev = qbo->tbo.base.dev->dev_private;

	if (bo->mem.mem_type == TTM_PL_PRIV && qbo->surface_id)
		qxl_surface_evict(qdev, qbo, new_mem ? true : false);
}