#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
struct TYPE_6__ {int /*<<< orphan*/  fc; } ;
struct pgid {TYPE_3__ inf; } ;
struct ccw_request {struct ccw1* cp; int /*<<< orphan*/  lpm; } ;
struct ccw_device {TYPE_2__* private; } ;
struct ccw1 {int count; int /*<<< orphan*/  flags; scalar_t__ cda; int /*<<< orphan*/  cmd_code; } ;
typedef  scalar_t__ addr_t ;
struct TYPE_5__ {TYPE_1__* dma_area; struct ccw_request req; } ;
struct TYPE_4__ {struct pgid* pgid; struct ccw1* iccws; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCW_CMD_SET_PGID ; 
 int /*<<< orphan*/  CCW_FLAG_SLI ; 
 int pathmask_to_pos (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void spid_build_cp(struct ccw_device *cdev, u8 fn)
{
	struct ccw_request *req = &cdev->private->req;
	struct ccw1 *cp = cdev->private->dma_area->iccws;
	int i = pathmask_to_pos(req->lpm);
	struct pgid *pgid = &cdev->private->dma_area->pgid[i];

	pgid->inf.fc	= fn;
	cp->cmd_code	= CCW_CMD_SET_PGID;
	cp->cda		= (u32) (addr_t) pgid;
	cp->count	= sizeof(*pgid);
	cp->flags	= CCW_FLAG_SLI;
	req->cp		= cp;
}