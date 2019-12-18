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
struct icc_path {int num_nodes; TYPE_2__* reqs; } ;
struct icc_node {TYPE_1__* provider; } ;
struct TYPE_4__ {struct icc_node* node; } ;
struct TYPE_3__ {int (* set ) (struct icc_node*,struct icc_node*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int stub1 (struct icc_node*,struct icc_node*) ; 

__attribute__((used)) static int apply_constraints(struct icc_path *path)
{
	struct icc_node *next, *prev = NULL;
	int ret = -EINVAL;
	int i;

	for (i = 0; i < path->num_nodes; i++) {
		next = path->reqs[i].node;

		/*
		 * Both endpoints should be valid master-slave pairs of the
		 * same interconnect provider that will be configured.
		 */
		if (!prev || next->provider != prev->provider) {
			prev = next;
			continue;
		}

		/* set the constraints */
		ret = next->provider->set(prev, next);
		if (ret)
			goto out;

		prev = next;
	}
out:
	return ret;
}