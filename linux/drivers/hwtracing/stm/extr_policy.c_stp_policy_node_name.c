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
struct TYPE_3__ {scalar_t__ ci_name; } ;
struct TYPE_4__ {TYPE_1__ cg_item; } ;
struct stp_policy_node {TYPE_2__ group; } ;

/* Variables and functions */

__attribute__((used)) static inline char *stp_policy_node_name(struct stp_policy_node *policy_node)
{
	return policy_node->group.cg_item.ci_name ? : "<none>";
}