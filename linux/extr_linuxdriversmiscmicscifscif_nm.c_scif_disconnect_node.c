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
typedef  size_t u32 ;
struct scif_dev {int /*<<< orphan*/  disconn_rescnt; int /*<<< orphan*/  disconn_wq; } ;
struct TYPE_2__ {size_t maxid; } ;

/* Variables and functions */
 size_t SCIF_MGMT_NODE ; 
 int /*<<< orphan*/  SCIF_NODE_ALIVE_TIMEOUT ; 
 scalar_t__ _scifdev_alive (struct scif_dev*) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct scif_dev* scif_dev ; 
 TYPE_1__ scif_info ; 
 int /*<<< orphan*/  scif_send_exit (struct scif_dev*) ; 
 int scif_send_rmnode_msg (size_t,size_t) ; 
 int wait_event_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

void scif_disconnect_node(u32 node_id, bool mgmt_initiated)
{
	int ret;
	int msg_cnt = 0;
	u32 i = 0;
	struct scif_dev *scifdev = &scif_dev[node_id];

	if (!node_id)
		return;

	atomic_set(&scifdev->disconn_rescnt, 0);

	/* Destroy p2p network */
	for (i = 1; i <= scif_info.maxid; i++) {
		if (i == node_id)
			continue;
		ret = scif_send_rmnode_msg(i, node_id);
		if (!ret)
			msg_cnt++;
	}
	/* Wait for the remote nodes to respond with SCIF_NODE_REMOVE_ACK */
	ret = wait_event_timeout(scifdev->disconn_wq,
				 (atomic_read(&scifdev->disconn_rescnt)
				 == msg_cnt), SCIF_NODE_ALIVE_TIMEOUT);
	/* Tell the card to clean up */
	if (mgmt_initiated && _scifdev_alive(scifdev))
		/*
		 * Send an SCIF_EXIT message which is the last message from Host
		 * to the MIC and wait for a SCIF_EXIT_ACK
		 */
		scif_send_exit(scifdev);
	atomic_set(&scifdev->disconn_rescnt, 0);
	/* Tell the mgmt node to clean up */
	ret = scif_send_rmnode_msg(SCIF_MGMT_NODE, node_id);
	if (!ret)
		/* Wait for mgmt node to respond with SCIF_NODE_REMOVE_ACK */
		wait_event_timeout(scifdev->disconn_wq,
				   (atomic_read(&scifdev->disconn_rescnt) == 1),
				   SCIF_NODE_ALIVE_TIMEOUT);
}