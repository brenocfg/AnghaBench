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
struct beiscsi_hba {int /*<<< orphan*/ ** ep_array; } ;
struct beiscsi_endpoint {struct beiscsi_conn* conn; int /*<<< orphan*/  ep_cid; struct beiscsi_hba* phba; } ;
struct beiscsi_conn {scalar_t__ login_in_progress; int /*<<< orphan*/  task; } ;

/* Variables and functions */
 size_t BE_GET_CRI_FROM_CID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  beiscsi_free_mgmt_task_handles (struct beiscsi_conn*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  beiscsi_put_cid (struct beiscsi_hba*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void beiscsi_free_ep(struct beiscsi_endpoint *beiscsi_ep)
{
	struct beiscsi_hba *phba = beiscsi_ep->phba;
	struct beiscsi_conn *beiscsi_conn;

	beiscsi_put_cid(phba, beiscsi_ep->ep_cid);
	beiscsi_ep->phba = NULL;
	/* clear this to track freeing in beiscsi_ep_disconnect */
	phba->ep_array[BE_GET_CRI_FROM_CID(beiscsi_ep->ep_cid)] = NULL;

	/**
	 * Check if any connection resource allocated by driver
	 * is to be freed.This case occurs when target redirection
	 * or connection retry is done.
	 **/
	if (!beiscsi_ep->conn)
		return;

	beiscsi_conn = beiscsi_ep->conn;
	/**
	 * Break ep->conn link here so that completions after
	 * this are ignored.
	 */
	beiscsi_ep->conn = NULL;
	if (beiscsi_conn->login_in_progress) {
		beiscsi_free_mgmt_task_handles(beiscsi_conn,
					       beiscsi_conn->task);
		beiscsi_conn->login_in_progress = 0;
	}
}