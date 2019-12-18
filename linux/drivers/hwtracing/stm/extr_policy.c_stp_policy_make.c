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
struct stm_protocol_driver {int dummy; } ;
struct stm_device {int /*<<< orphan*/  policy_mutex; TYPE_1__* policy; struct config_item_type const* pdrv_node_type; struct stm_protocol_driver const* pdrv; } ;
struct config_item_type {int dummy; } ;
struct config_group {int dummy; } ;
struct TYPE_2__ {struct config_group group; struct stm_device* stm; } ;

/* Variables and functions */
 int /*<<< orphan*/  EBUSY ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENODEV ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct config_group* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct config_group*) ; 
 int /*<<< orphan*/  config_group_init_type_name (struct config_group*,char const*,int /*<<< orphan*/ *) ; 
 char* kasprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 TYPE_1__* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct stm_device* stm_find_device (char*) ; 
 int stm_lookup_protocol (char*,struct stm_protocol_driver const**,struct config_item_type const**) ; 
 int /*<<< orphan*/  stm_put_device (struct stm_device*) ; 
 int /*<<< orphan*/  stm_put_protocol (struct stm_protocol_driver const*) ; 
 int /*<<< orphan*/  stp_policy_type ; 
 char* strrchr (char*,char) ; 

__attribute__((used)) static struct config_group *
stp_policy_make(struct config_group *group, const char *name)
{
	const struct config_item_type *pdrv_node_type;
	const struct stm_protocol_driver *pdrv;
	char *devname, *proto, *p;
	struct config_group *ret;
	struct stm_device *stm;
	int err;

	devname = kasprintf(GFP_KERNEL, "%s", name);
	if (!devname)
		return ERR_PTR(-ENOMEM);

	/*
	 * node must look like <device_name>.<policy_name>, where
	 * <device_name> is the name of an existing stm device; may
	 *               contain dots;
	 * <policy_name> is an arbitrary string; may not contain dots
	 * <device_name>:<protocol_name>.<policy_name>
	 */
	p = strrchr(devname, '.');
	if (!p) {
		kfree(devname);
		return ERR_PTR(-EINVAL);
	}

	*p = '\0';

	/*
	 * look for ":<protocol_name>":
	 *  + no protocol suffix: fall back to whatever is available;
	 *  + unknown protocol: fail the whole thing
	 */
	proto = strrchr(devname, ':');
	if (proto)
		*proto++ = '\0';

	stm = stm_find_device(devname);
	if (!stm) {
		kfree(devname);
		return ERR_PTR(-ENODEV);
	}

	err = stm_lookup_protocol(proto, &pdrv, &pdrv_node_type);
	kfree(devname);

	if (err) {
		stm_put_device(stm);
		return ERR_PTR(-ENODEV);
	}

	mutex_lock(&stm->policy_mutex);
	if (stm->policy) {
		ret = ERR_PTR(-EBUSY);
		goto unlock_policy;
	}

	stm->policy = kzalloc(sizeof(*stm->policy), GFP_KERNEL);
	if (!stm->policy) {
		ret = ERR_PTR(-ENOMEM);
		goto unlock_policy;
	}

	config_group_init_type_name(&stm->policy->group, name,
				    &stp_policy_type);

	stm->pdrv = pdrv;
	stm->pdrv_node_type = pdrv_node_type;
	stm->policy->stm = stm;
	ret = &stm->policy->group;

unlock_policy:
	mutex_unlock(&stm->policy_mutex);

	if (IS_ERR(ret)) {
		/*
		 * pdrv and stm->pdrv at this point can be quite different,
		 * and only one of them needs to be 'put'
		 */
		stm_put_protocol(pdrv);
		stm_put_device(stm);
	}

	return ret;
}