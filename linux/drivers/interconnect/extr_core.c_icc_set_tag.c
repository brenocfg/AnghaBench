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
typedef  int /*<<< orphan*/  u32 ;
struct icc_path {int num_nodes; TYPE_1__* reqs; } ;
struct TYPE_2__ {int /*<<< orphan*/  tag; } ;

/* Variables and functions */
 int /*<<< orphan*/  icc_lock ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void icc_set_tag(struct icc_path *path, u32 tag)
{
	int i;

	if (!path)
		return;

	mutex_lock(&icc_lock);

	for (i = 0; i < path->num_nodes; i++)
		path->reqs[i].tag = tag;

	mutex_unlock(&icc_lock);
}