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
struct TYPE_2__ {int msg; } ;
union nic_mbx {TYPE_1__ msg; } ;
struct nicvf {int pf_acked; int pf_nacked; int /*<<< orphan*/  rx_mode_mtx; int /*<<< orphan*/  vf_id; int /*<<< orphan*/  netdev; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int NIC_MBOX_MSG_TIMEOUT ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nicvf_write_to_mbx (struct nicvf*,union nic_mbx*) ; 

int nicvf_send_msg_to_pf(struct nicvf *nic, union nic_mbx *mbx)
{
	int timeout = NIC_MBOX_MSG_TIMEOUT;
	int sleep = 10;
	int ret = 0;

	mutex_lock(&nic->rx_mode_mtx);

	nic->pf_acked = false;
	nic->pf_nacked = false;

	nicvf_write_to_mbx(nic, mbx);

	/* Wait for previous message to be acked, timeout 2sec */
	while (!nic->pf_acked) {
		if (nic->pf_nacked) {
			netdev_err(nic->netdev,
				   "PF NACK to mbox msg 0x%02x from VF%d\n",
				   (mbx->msg.msg & 0xFF), nic->vf_id);
			ret = -EINVAL;
			break;
		}
		msleep(sleep);
		if (nic->pf_acked)
			break;
		timeout -= sleep;
		if (!timeout) {
			netdev_err(nic->netdev,
				   "PF didn't ACK to mbox msg 0x%02x from VF%d\n",
				   (mbx->msg.msg & 0xFF), nic->vf_id);
			ret = -EBUSY;
			break;
		}
	}
	mutex_unlock(&nic->rx_mode_mtx);
	return ret;
}