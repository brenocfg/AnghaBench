#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {TYPE_2__* update_cache; TYPE_7__* write_cache; TYPE_4__* read_cache; } ;
struct spinand_device {int flags; TYPE_6__ op_templates; } ;
struct TYPE_12__ {int buswidth; } ;
struct TYPE_14__ {TYPE_5__ data; } ;
struct TYPE_10__ {int buswidth; } ;
struct TYPE_11__ {TYPE_3__ data; } ;
struct TYPE_8__ {int buswidth; } ;
struct TYPE_9__ {TYPE_1__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  CFG_QUAD_ENABLE ; 
 int SPINAND_HAS_QE_BIT ; 
 int spinand_upd_cfg (struct spinand_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int spinand_init_quad_enable(struct spinand_device *spinand)
{
	bool enable = false;

	if (!(spinand->flags & SPINAND_HAS_QE_BIT))
		return 0;

	if (spinand->op_templates.read_cache->data.buswidth == 4 ||
	    spinand->op_templates.write_cache->data.buswidth == 4 ||
	    spinand->op_templates.update_cache->data.buswidth == 4)
		enable = true;

	return spinand_upd_cfg(spinand, CFG_QUAD_ENABLE,
			       enable ? CFG_QUAD_ENABLE : 0);
}