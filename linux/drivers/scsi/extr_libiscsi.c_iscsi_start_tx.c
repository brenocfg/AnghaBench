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
struct iscsi_conn {int /*<<< orphan*/  suspend_tx; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISCSI_SUSPEND_BIT ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iscsi_conn_queue_work (struct iscsi_conn*) ; 

__attribute__((used)) static void iscsi_start_tx(struct iscsi_conn *conn)
{
	clear_bit(ISCSI_SUSPEND_BIT, &conn->suspend_tx);
	iscsi_conn_queue_work(conn);
}