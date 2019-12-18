#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct vp_ctrl_entry_24xx {int entry_count; int* vp_idx_map; void* vp_count; void* command; int /*<<< orphan*/  handle; int /*<<< orphan*/  entry_type; } ;
struct TYPE_7__ {int cmd; int vp_index; } ;
struct TYPE_8__ {TYPE_1__ ctrlvp; } ;
struct TYPE_9__ {TYPE_2__ u; } ;
struct TYPE_10__ {TYPE_3__ iocb_cmd; } ;
struct TYPE_11__ {TYPE_4__ u; int /*<<< orphan*/  handle; } ;
typedef  TYPE_5__ srb_t ;

/* Variables and functions */
 int /*<<< orphan*/  VP_CTRL_IOCB_TYPE ; 
 void* cpu_to_le16 (int) ; 

__attribute__((used)) static void
qla25xx_ctrlvp_iocb(srb_t *sp, struct vp_ctrl_entry_24xx *vce)
{
	int map, pos;

	vce->entry_type = VP_CTRL_IOCB_TYPE;
	vce->handle = sp->handle;
	vce->entry_count = 1;
	vce->command = cpu_to_le16(sp->u.iocb_cmd.u.ctrlvp.cmd);
	vce->vp_count = cpu_to_le16(1);

	/*
	 * index map in firmware starts with 1; decrement index
	 * this is ok as we never use index 0
	 */
	map = (sp->u.iocb_cmd.u.ctrlvp.vp_index - 1) / 8;
	pos = (sp->u.iocb_cmd.u.ctrlvp.vp_index - 1) & 7;
	vce->vp_idx_map[map] |= 1 << pos;
}