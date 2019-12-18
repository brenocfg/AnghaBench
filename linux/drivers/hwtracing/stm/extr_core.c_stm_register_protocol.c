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
struct stm_protocol_driver {scalar_t__ policy_attr; int /*<<< orphan*/  name; } ;
struct stm_pdrv_entry {struct stm_protocol_driver const* pdrv; int /*<<< orphan*/  entry; int /*<<< orphan*/  node_type; } ;

/* Variables and functions */
 int EEXIST ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ __stm_lookup_protocol (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_policy_node_type (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct stm_pdrv_entry*) ; 
 struct stm_pdrv_entry* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stm_pdrv_head ; 
 int /*<<< orphan*/  stm_pdrv_mutex ; 

int stm_register_protocol(const struct stm_protocol_driver *pdrv)
{
	struct stm_pdrv_entry *pe = NULL;
	int ret = -ENOMEM;

	mutex_lock(&stm_pdrv_mutex);

	if (__stm_lookup_protocol(pdrv->name)) {
		ret = -EEXIST;
		goto unlock;
	}

	pe = kzalloc(sizeof(*pe), GFP_KERNEL);
	if (!pe)
		goto unlock;

	if (pdrv->policy_attr) {
		pe->node_type = get_policy_node_type(pdrv->policy_attr);
		if (!pe->node_type)
			goto unlock;
	}

	list_add_tail(&pe->entry, &stm_pdrv_head);
	pe->pdrv = pdrv;

	ret = 0;
unlock:
	mutex_unlock(&stm_pdrv_mutex);

	if (ret)
		kfree(pe);

	return ret;
}