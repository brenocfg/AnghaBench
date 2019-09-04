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
struct sk_buff {int dummy; } ;
struct nlattr {int dummy; } ;
struct netlink_callback {long* args; int /*<<< orphan*/  nlh; } ;
struct drbd_resource {int /*<<< orphan*/  kref; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRBD_NLA_CFG_CONTEXT ; 
 int EINVAL ; 
 int ENODEV ; 
 unsigned int GENL_HDRLEN ; 
 unsigned int GENL_MAGIC_FAMILY_HDRSZ ; 
 scalar_t__ IS_ERR (struct nlattr*) ; 
 int PTR_ERR (struct nlattr*) ; 
 int /*<<< orphan*/  T_ctx_resource_name ; 
 int /*<<< orphan*/  __nla_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drbd_cfg_context_nl_policy ; 
 int /*<<< orphan*/  drbd_destroy_resource ; 
 struct drbd_resource* drbd_find_resource (char const*) ; 
 struct nlattr* drbd_nla_find_nested (int,struct nlattr*,int /*<<< orphan*/ ) ; 
 int get_one_status (struct sk_buff*,struct netlink_callback*) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* nla_data (struct nlattr*) ; 
 struct nlattr* nla_find (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlmsg_attrdata (int /*<<< orphan*/ ,unsigned int const) ; 
 int /*<<< orphan*/  nlmsg_attrlen (int /*<<< orphan*/ ,unsigned int const) ; 

int drbd_adm_get_status_all(struct sk_buff *skb, struct netlink_callback *cb)
{
	const unsigned hdrlen = GENL_HDRLEN + GENL_MAGIC_FAMILY_HDRSZ;
	struct nlattr *nla;
	const char *resource_name;
	struct drbd_resource *resource;
	int maxtype;

	/* Is this a followup call? */
	if (cb->args[0]) {
		/* ... of a single resource dump,
		 * and the resource iterator has been advanced already? */
		if (cb->args[2] && cb->args[2] != cb->args[0])
			return 0; /* DONE. */
		goto dump;
	}

	/* First call (from netlink_dump_start).  We need to figure out
	 * which resource(s) the user wants us to dump. */
	nla = nla_find(nlmsg_attrdata(cb->nlh, hdrlen),
			nlmsg_attrlen(cb->nlh, hdrlen),
			DRBD_NLA_CFG_CONTEXT);

	/* No explicit context given.  Dump all. */
	if (!nla)
		goto dump;
	maxtype = ARRAY_SIZE(drbd_cfg_context_nl_policy) - 1;
	nla = drbd_nla_find_nested(maxtype, nla, __nla_type(T_ctx_resource_name));
	if (IS_ERR(nla))
		return PTR_ERR(nla);
	/* context given, but no name present? */
	if (!nla)
		return -EINVAL;
	resource_name = nla_data(nla);
	if (!*resource_name)
		return -ENODEV;
	resource = drbd_find_resource(resource_name);
	if (!resource)
		return -ENODEV;

	kref_put(&resource->kref, drbd_destroy_resource); /* get_one_status() revalidates the resource */

	/* prime iterators, and set "filter" mode mark:
	 * only dump this connection. */
	cb->args[0] = (long)resource;
	/* cb->args[1] = 0; passed in this way. */
	cb->args[2] = (long)resource;

dump:
	return get_one_status(skb, cb);
}