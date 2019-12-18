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
struct mad_rmpp_recv {int /*<<< orphan*/  list; int /*<<< orphan*/  rmpp_wc; } ;
struct ib_mad_agent_private {int /*<<< orphan*/  rmpp_list; } ;

/* Variables and functions */
 struct mad_rmpp_recv* find_rmpp_recv (struct ib_mad_agent_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct mad_rmpp_recv *
insert_rmpp_recv(struct ib_mad_agent_private *agent,
		 struct mad_rmpp_recv *rmpp_recv)
{
	struct mad_rmpp_recv *cur_rmpp_recv;

	cur_rmpp_recv = find_rmpp_recv(agent, rmpp_recv->rmpp_wc);
	if (!cur_rmpp_recv)
		list_add_tail(&rmpp_recv->list, &agent->rmpp_list);

	return cur_rmpp_recv;
}