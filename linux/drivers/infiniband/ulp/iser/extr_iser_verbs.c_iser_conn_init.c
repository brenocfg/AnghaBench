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
struct TYPE_2__ {int /*<<< orphan*/  done; } ;
struct ib_conn {TYPE_1__ reg_cqe; scalar_t__ post_recv_buf_count; } ;
struct iser_conn {int /*<<< orphan*/  state_mutex; int /*<<< orphan*/  conn_list; int /*<<< orphan*/  up_completion; int /*<<< orphan*/  ib_completion; int /*<<< orphan*/  stop_completion; int /*<<< orphan*/  state; struct ib_conn ib_conn; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ISER_CONN_INIT ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iser_reg_comp ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

void iser_conn_init(struct iser_conn *iser_conn)
{
	struct ib_conn *ib_conn = &iser_conn->ib_conn;

	iser_conn->state = ISER_CONN_INIT;
	init_completion(&iser_conn->stop_completion);
	init_completion(&iser_conn->ib_completion);
	init_completion(&iser_conn->up_completion);
	INIT_LIST_HEAD(&iser_conn->conn_list);
	mutex_init(&iser_conn->state_mutex);

	ib_conn->post_recv_buf_count = 0;
	ib_conn->reg_cqe.done = iser_reg_comp;
}