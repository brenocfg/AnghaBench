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
typedef  int u8 ;
struct scif_dev {int node; int /*<<< orphan*/  spdev; int /*<<< orphan*/  p2p; int /*<<< orphan*/  qp_dwork; int /*<<< orphan*/  p2p_dwork; int /*<<< orphan*/  peer_add_work; int /*<<< orphan*/  lock; int /*<<< orphan*/  disconn_wq; int /*<<< orphan*/  exit; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int MAX_SCIF_NODES ; 
 int /*<<< orphan*/  OP_IDLE ; 
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 struct scif_dev* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scif_add_peer_device ; 
 struct scif_dev* scif_dev ; 
 int /*<<< orphan*/  scif_poll_qp_state ; 
 int /*<<< orphan*/  scif_qp_setup_handler ; 

__attribute__((used)) static int scif_setup_scifdev(void)
{
	/* We support a maximum of 129 SCIF nodes including the mgmt node */
#define MAX_SCIF_NODES 129
	int i;
	u8 num_nodes = MAX_SCIF_NODES;

	scif_dev = kcalloc(num_nodes, sizeof(*scif_dev), GFP_KERNEL);
	if (!scif_dev)
		return -ENOMEM;
	for (i = 0; i < num_nodes; i++) {
		struct scif_dev *scifdev = &scif_dev[i];

		scifdev->node = i;
		scifdev->exit = OP_IDLE;
		init_waitqueue_head(&scifdev->disconn_wq);
		mutex_init(&scifdev->lock);
		INIT_WORK(&scifdev->peer_add_work, scif_add_peer_device);
		INIT_DELAYED_WORK(&scifdev->p2p_dwork,
				  scif_poll_qp_state);
		INIT_DELAYED_WORK(&scifdev->qp_dwork,
				  scif_qp_setup_handler);
		INIT_LIST_HEAD(&scifdev->p2p);
		RCU_INIT_POINTER(scifdev->spdev, NULL);
	}
	return 0;
}