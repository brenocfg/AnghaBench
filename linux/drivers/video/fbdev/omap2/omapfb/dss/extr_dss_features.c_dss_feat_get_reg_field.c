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
typedef  enum dss_feat_reg_field { ____Placeholder_dss_feat_reg_field } dss_feat_reg_field ;
struct TYPE_4__ {int num_reg_fields; TYPE_1__* reg_fields; } ;
struct TYPE_3__ {int /*<<< orphan*/  end; int /*<<< orphan*/  start; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 TYPE_2__* omap_current_dss_features ; 

void dss_feat_get_reg_field(enum dss_feat_reg_field id, u8 *start, u8 *end)
{
	BUG_ON(id >= omap_current_dss_features->num_reg_fields);

	*start = omap_current_dss_features->reg_fields[id].start;
	*end = omap_current_dss_features->reg_fields[id].end;
}