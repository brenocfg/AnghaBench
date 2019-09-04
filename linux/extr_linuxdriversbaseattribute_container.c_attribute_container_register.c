#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct attribute_container {int /*<<< orphan*/  node; int /*<<< orphan*/  containers; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  attribute_container_list ; 
 int /*<<< orphan*/  attribute_container_mutex ; 
 int /*<<< orphan*/  internal_container_klist_get ; 
 int /*<<< orphan*/  internal_container_klist_put ; 
 int /*<<< orphan*/  klist_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int
attribute_container_register(struct attribute_container *cont)
{
	INIT_LIST_HEAD(&cont->node);
	klist_init(&cont->containers, internal_container_klist_get,
		   internal_container_klist_put);

	mutex_lock(&attribute_container_mutex);
	list_add_tail(&cont->node, &attribute_container_list);
	mutex_unlock(&attribute_container_mutex);

	return 0;
}