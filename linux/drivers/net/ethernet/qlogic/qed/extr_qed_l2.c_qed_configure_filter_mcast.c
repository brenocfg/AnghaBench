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
struct qed_filter_mcast_params {int type; int num; int /*<<< orphan*/ * mac; } ;
struct qed_filter_mcast {int num_mc_addrs; int /*<<< orphan*/ * mac; int /*<<< orphan*/  opcode; } ;
struct qed_dev {int dummy; } ;
typedef  int /*<<< orphan*/  mcast ;

/* Variables and functions */
 int /*<<< orphan*/  DP_NOTICE (struct qed_dev*,char*,int) ; 
 int /*<<< orphan*/  QED_FILTER_ADD ; 
 int /*<<< orphan*/  QED_FILTER_REMOVE ; 
#define  QED_FILTER_XCAST_TYPE_ADD 129 
#define  QED_FILTER_XCAST_TYPE_DEL 128 
 int /*<<< orphan*/  QED_SPQ_MODE_CB ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct qed_filter_mcast*,int /*<<< orphan*/ ,int) ; 
 int qed_filter_mcast_cmd (struct qed_dev*,struct qed_filter_mcast*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qed_configure_filter_mcast(struct qed_dev *cdev,
				      struct qed_filter_mcast_params *params)
{
	struct qed_filter_mcast mcast;
	int i;

	memset(&mcast, 0, sizeof(mcast));
	switch (params->type) {
	case QED_FILTER_XCAST_TYPE_ADD:
		mcast.opcode = QED_FILTER_ADD;
		break;
	case QED_FILTER_XCAST_TYPE_DEL:
		mcast.opcode = QED_FILTER_REMOVE;
		break;
	default:
		DP_NOTICE(cdev, "Unknown multicast filter type %d\n",
			  params->type);
	}

	mcast.num_mc_addrs = params->num;
	for (i = 0; i < mcast.num_mc_addrs; i++)
		ether_addr_copy(mcast.mac[i], params->mac[i]);

	return qed_filter_mcast_cmd(cdev, &mcast, QED_SPQ_MODE_CB, NULL);
}