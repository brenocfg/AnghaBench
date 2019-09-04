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
struct isert_conn {int /*<<< orphan*/  qp; } ;
struct iscsi_conn {struct isert_conn* context; } ;

/* Variables and functions */
 int /*<<< orphan*/  ib_drain_qp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isert_put_conn (struct isert_conn*) ; 

__attribute__((used)) static void isert_free_conn(struct iscsi_conn *conn)
{
	struct isert_conn *isert_conn = conn->context;

	ib_drain_qp(isert_conn->qp);
	isert_put_conn(isert_conn);
}