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
struct cpl_abort_rpl {int cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPL_ABORT_RPL ; 
 int /*<<< orphan*/  INIT_TP_WR_CPL (struct cpl_abort_rpl*,int /*<<< orphan*/ ,unsigned int) ; 
 struct cpl_abort_rpl* cplhdr (struct sk_buff*) ; 

__attribute__((used)) static void set_abort_rpl_wr(struct sk_buff *skb, unsigned int tid,
			     int cmd)
{
	struct cpl_abort_rpl *rpl = cplhdr(skb);

	INIT_TP_WR_CPL(rpl, CPL_ABORT_RPL, tid);
	rpl->cmd = cmd;
}