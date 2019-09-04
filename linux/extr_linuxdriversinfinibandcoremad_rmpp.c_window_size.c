#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ib_mad_agent_private {TYPE_2__* qp_info; } ;
struct TYPE_3__ {int max_active; } ;
struct TYPE_4__ {TYPE_1__ recv_queue; } ;

/* Variables and functions */
 int max (int,int) ; 

__attribute__((used)) static inline int window_size(struct ib_mad_agent_private *agent)
{
	return max(agent->qp_info->recv_queue.max_active >> 3, 1);
}