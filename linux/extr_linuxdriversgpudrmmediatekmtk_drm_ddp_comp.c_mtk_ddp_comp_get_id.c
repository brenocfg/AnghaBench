#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct device_node {int dummy; } ;
typedef  enum mtk_ddp_comp_type { ____Placeholder_mtk_ddp_comp_type } mtk_ddp_comp_type ;
struct TYPE_3__ {int type; int alias_id; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int EINVAL ; 
 int /*<<< orphan*/ * mtk_ddp_comp_stem ; 
 TYPE_1__* mtk_ddp_matches ; 
 int of_alias_get_id (struct device_node*,int /*<<< orphan*/ ) ; 

int mtk_ddp_comp_get_id(struct device_node *node,
			enum mtk_ddp_comp_type comp_type)
{
	int id = of_alias_get_id(node, mtk_ddp_comp_stem[comp_type]);
	int i;

	for (i = 0; i < ARRAY_SIZE(mtk_ddp_matches); i++) {
		if (comp_type == mtk_ddp_matches[i].type &&
		    (id < 0 || id == mtk_ddp_matches[i].alias_id))
			return i;
	}

	return -EINVAL;
}