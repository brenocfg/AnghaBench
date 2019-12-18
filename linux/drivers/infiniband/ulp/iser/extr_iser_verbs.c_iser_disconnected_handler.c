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
struct rdma_cm_id {scalar_t__ context; } ;
struct iser_conn {scalar_t__ iscsi_conn; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISCSI_ERR_CONN_FAILED ; 
 int /*<<< orphan*/  iscsi_conn_failure (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ iser_conn_terminate (struct iser_conn*) ; 
 int /*<<< orphan*/  iser_err (char*) ; 

__attribute__((used)) static void iser_disconnected_handler(struct rdma_cm_id *cma_id)
{
	struct iser_conn *iser_conn = (struct iser_conn *)cma_id->context;

	if (iser_conn_terminate(iser_conn)) {
		if (iser_conn->iscsi_conn)
			iscsi_conn_failure(iser_conn->iscsi_conn,
					   ISCSI_ERR_CONN_FAILED);
		else
			iser_err("iscsi_iser connection isn't bound\n");
	}
}