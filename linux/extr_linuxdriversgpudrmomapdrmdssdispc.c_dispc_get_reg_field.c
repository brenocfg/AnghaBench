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
typedef  int /*<<< orphan*/  u8 ;
struct dispc_device {TYPE_2__* feat; } ;
typedef  enum dispc_feat_reg_field { ____Placeholder_dispc_feat_reg_field } dispc_feat_reg_field ;
struct TYPE_4__ {int num_reg_fields; TYPE_1__* reg_fields; } ;
struct TYPE_3__ {int /*<<< orphan*/  end; int /*<<< orphan*/  start; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 

__attribute__((used)) static void dispc_get_reg_field(struct dispc_device *dispc,
				enum dispc_feat_reg_field id,
				u8 *start, u8 *end)
{
	if (id >= dispc->feat->num_reg_fields)
		BUG();

	*start = dispc->feat->reg_fields[id].start;
	*end = dispc->feat->reg_fields[id].end;
}