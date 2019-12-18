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
struct ib_mad_qp_info {int /*<<< orphan*/  snoop_count; scalar_t__ snoop_table_size; int /*<<< orphan*/ * snoop_table; int /*<<< orphan*/  snoop_lock; int /*<<< orphan*/  overflow_list; int /*<<< orphan*/  recv_queue; int /*<<< orphan*/  send_queue; struct ib_mad_port_private* port_priv; } ;
struct ib_mad_port_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_mad_queue (struct ib_mad_qp_info*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void init_mad_qp(struct ib_mad_port_private *port_priv,
			struct ib_mad_qp_info *qp_info)
{
	qp_info->port_priv = port_priv;
	init_mad_queue(qp_info, &qp_info->send_queue);
	init_mad_queue(qp_info, &qp_info->recv_queue);
	INIT_LIST_HEAD(&qp_info->overflow_list);
	spin_lock_init(&qp_info->snoop_lock);
	qp_info->snoop_table = NULL;
	qp_info->snoop_table_size = 0;
	atomic_set(&qp_info->snoop_count, 0);
}