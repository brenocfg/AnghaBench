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
struct t3cdev {int dummy; } ;
struct sk_buff {int dummy; } ;
struct cpl_rte_write_rpl {scalar_t__ status; } ;

/* Variables and functions */
 scalar_t__ CPL_ERR_NONE ; 
 int CPL_RET_BUF_DONE ; 
 int /*<<< orphan*/  GET_TID (struct cpl_rte_write_rpl*) ; 
 struct cpl_rte_write_rpl* cplhdr (struct sk_buff*) ; 
 int /*<<< orphan*/  pr_err (char*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int do_rte_write_rpl(struct t3cdev *dev, struct sk_buff *skb)
{
	struct cpl_rte_write_rpl *rpl = cplhdr(skb);

	if (rpl->status != CPL_ERR_NONE)
		pr_err("Unexpected RTE_WRITE_RPL status %u for entry %u\n",
		       rpl->status, GET_TID(rpl));

	return CPL_RET_BUF_DONE;
}