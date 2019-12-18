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
struct TYPE_2__ {int /*<<< orphan*/  type; } ;
struct mlx5_flow_rule {int /*<<< orphan*/  dest_attr; TYPE_1__ node; int /*<<< orphan*/  next_ft; } ;
struct mlx5_flow_destination {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FS_TYPE_FLOW_DEST ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct mlx5_flow_rule* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct mlx5_flow_destination*,int) ; 

__attribute__((used)) static struct mlx5_flow_rule *alloc_rule(struct mlx5_flow_destination *dest)
{
	struct mlx5_flow_rule *rule;

	rule = kzalloc(sizeof(*rule), GFP_KERNEL);
	if (!rule)
		return NULL;

	INIT_LIST_HEAD(&rule->next_ft);
	rule->node.type = FS_TYPE_FLOW_DEST;
	if (dest)
		memcpy(&rule->dest_attr, dest, sizeof(*dest));

	return rule;
}