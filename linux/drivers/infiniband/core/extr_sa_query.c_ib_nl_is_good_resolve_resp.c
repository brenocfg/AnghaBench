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
struct nlmsghdr {int nlmsg_flags; } ;
struct nlattr {int dummy; } ;

/* Variables and functions */
 int LS_NLA_TYPE_MAX ; 
 int RDMA_NL_LS_F_ERR ; 
 int /*<<< orphan*/  ib_nl_policy ; 
 int nla_parse_deprecated (struct nlattr**,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nlmsg_data (struct nlmsghdr const*) ; 
 int /*<<< orphan*/  nlmsg_len (struct nlmsghdr const*) ; 

__attribute__((used)) static inline int ib_nl_is_good_resolve_resp(const struct nlmsghdr *nlh)
{
	struct nlattr *tb[LS_NLA_TYPE_MAX];
	int ret;

	if (nlh->nlmsg_flags & RDMA_NL_LS_F_ERR)
		return 0;

	ret = nla_parse_deprecated(tb, LS_NLA_TYPE_MAX - 1, nlmsg_data(nlh),
				   nlmsg_len(nlh), ib_nl_policy, NULL);
	if (ret)
		return 0;

	return 1;
}