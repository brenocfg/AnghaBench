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
struct TYPE_2__ {int /*<<< orphan*/  b; } ;
struct sys_t_policy_node {TYPE_1__ uuid; } ;

/* Variables and functions */
 int /*<<< orphan*/  generate_random_uuid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sys_t_policy_node_init(void *priv)
{
	struct sys_t_policy_node *pn = priv;

	generate_random_uuid(pn->uuid.b);
}