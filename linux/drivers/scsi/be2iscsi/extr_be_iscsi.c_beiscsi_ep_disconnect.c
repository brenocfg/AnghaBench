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
typedef  size_t uint16_t ;
struct iscsi_endpoint {struct beiscsi_endpoint* dd_data; } ;
struct beiscsi_hba {int /*<<< orphan*/ ** conn_table; int /*<<< orphan*/  state; int /*<<< orphan*/ * ep_array; } ;
struct beiscsi_endpoint {int /*<<< orphan*/  openiscsi_ep; int /*<<< orphan*/  ep_cid; struct beiscsi_conn* conn; struct beiscsi_hba* phba; } ;
struct beiscsi_conn {int /*<<< orphan*/  conn; } ;

/* Variables and functions */
 int /*<<< orphan*/  BEISCSI_LOG_CONFIG ; 
 size_t BE_GET_CRI_FROM_CID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  __beiscsi_log (struct beiscsi_hba*,int /*<<< orphan*/ ,char*,size_t,...) ; 
 scalar_t__ beiscsi_conn_close (struct beiscsi_endpoint*) ; 
 int /*<<< orphan*/  beiscsi_free_ep (struct beiscsi_endpoint*) ; 
 int /*<<< orphan*/  beiscsi_hba_is_online (struct beiscsi_hba*) ; 
 int /*<<< orphan*/  beiscsi_log (struct beiscsi_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iscsi_destroy_endpoint (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iscsi_suspend_queue (int /*<<< orphan*/ ) ; 

void beiscsi_ep_disconnect(struct iscsi_endpoint *ep)
{
	struct beiscsi_endpoint *beiscsi_ep;
	struct beiscsi_conn *beiscsi_conn;
	struct beiscsi_hba *phba;
	uint16_t cri_index;

	beiscsi_ep = ep->dd_data;
	phba = beiscsi_ep->phba;
	beiscsi_log(phba, KERN_INFO, BEISCSI_LOG_CONFIG,
		    "BS_%d : In beiscsi_ep_disconnect for ep_cid = %u\n",
		    beiscsi_ep->ep_cid);

	cri_index = BE_GET_CRI_FROM_CID(beiscsi_ep->ep_cid);
	if (!phba->ep_array[cri_index]) {
		__beiscsi_log(phba, KERN_ERR,
			      "BS_%d : ep_array at %u cid %u empty\n",
			      cri_index,
			      beiscsi_ep->ep_cid);
		return;
	}

	if (beiscsi_ep->conn) {
		beiscsi_conn = beiscsi_ep->conn;
		iscsi_suspend_queue(beiscsi_conn->conn);
	}

	if (!beiscsi_hba_is_online(phba)) {
		beiscsi_log(phba, KERN_INFO, BEISCSI_LOG_CONFIG,
			    "BS_%d : HBA in error 0x%lx\n", phba->state);
	} else {
		/**
		 * Make CID available even if close fails.
		 * If not freed, FW might fail open using the CID.
		 */
		if (beiscsi_conn_close(beiscsi_ep) < 0)
			__beiscsi_log(phba, KERN_ERR,
				      "BS_%d : close conn failed cid %d\n",
				      beiscsi_ep->ep_cid);
	}

	beiscsi_free_ep(beiscsi_ep);
	if (!phba->conn_table[cri_index])
		__beiscsi_log(phba, KERN_ERR,
			      "BS_%d : conn_table empty at %u: cid %u\n",
			      cri_index, beiscsi_ep->ep_cid);
	phba->conn_table[cri_index] = NULL;
	iscsi_destroy_endpoint(beiscsi_ep->openiscsi_ep);
}