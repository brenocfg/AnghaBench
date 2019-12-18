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
typedef  int /*<<< orphan*/  u64 ;
struct sk_buff {int dummy; } ;
struct nlattr {int dummy; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 int /*<<< orphan*/  RDMA_NLDEV_ATTR_PAD ; 
 int /*<<< orphan*/  RDMA_NLDEV_ATTR_RES_SUMMARY_ENTRY ; 
 int /*<<< orphan*/  RDMA_NLDEV_ATTR_RES_SUMMARY_ENTRY_CURR ; 
 int /*<<< orphan*/  RDMA_NLDEV_ATTR_RES_SUMMARY_ENTRY_NAME ; 
 int /*<<< orphan*/  nla_nest_cancel (struct sk_buff*,struct nlattr*) ; 
 int /*<<< orphan*/  nla_nest_end (struct sk_buff*,struct nlattr*) ; 
 struct nlattr* nla_nest_start_noflag (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_string (struct sk_buff*,int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ nla_put_u64_64bit (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fill_res_info_entry(struct sk_buff *msg,
			       const char *name, u64 curr)
{
	struct nlattr *entry_attr;

	entry_attr = nla_nest_start_noflag(msg,
					   RDMA_NLDEV_ATTR_RES_SUMMARY_ENTRY);
	if (!entry_attr)
		return -EMSGSIZE;

	if (nla_put_string(msg, RDMA_NLDEV_ATTR_RES_SUMMARY_ENTRY_NAME, name))
		goto err;
	if (nla_put_u64_64bit(msg, RDMA_NLDEV_ATTR_RES_SUMMARY_ENTRY_CURR, curr,
			      RDMA_NLDEV_ATTR_PAD))
		goto err;

	nla_nest_end(msg, entry_attr);
	return 0;

err:
	nla_nest_cancel(msg, entry_attr);
	return -EMSGSIZE;
}