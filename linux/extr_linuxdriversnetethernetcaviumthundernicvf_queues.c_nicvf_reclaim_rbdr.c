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
typedef  int u64 ;
struct rbdr {int head; int tail; } ;
struct nicvf {int /*<<< orphan*/  netdev; } ;

/* Variables and functions */
 int NICVF_RBDR_RESET ; 
 int /*<<< orphan*/  NIC_QSET_RBDR_0_1_CFG ; 
 int /*<<< orphan*/  NIC_QSET_RBDR_0_1_HEAD ; 
 int /*<<< orphan*/  NIC_QSET_RBDR_0_1_PREFETCH_STATUS ; 
 int /*<<< orphan*/  NIC_QSET_RBDR_0_1_STATUS0 ; 
 int /*<<< orphan*/  NIC_QSET_RBDR_0_1_TAIL ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ nicvf_poll_reg (struct nicvf*,int,int /*<<< orphan*/ ,int,int,int) ; 
 int nicvf_queue_reg_read (struct nicvf*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nicvf_queue_reg_write (struct nicvf*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void nicvf_reclaim_rbdr(struct nicvf *nic,
			       struct rbdr *rbdr, int qidx)
{
	u64 tmp, fifo_state;
	int timeout = 10;

	/* Save head and tail pointers for feeing up buffers */
	rbdr->head = nicvf_queue_reg_read(nic,
					  NIC_QSET_RBDR_0_1_HEAD,
					  qidx) >> 3;
	rbdr->tail = nicvf_queue_reg_read(nic,
					  NIC_QSET_RBDR_0_1_TAIL,
					  qidx) >> 3;

	/* If RBDR FIFO is in 'FAIL' state then do a reset first
	 * before relaiming.
	 */
	fifo_state = nicvf_queue_reg_read(nic, NIC_QSET_RBDR_0_1_STATUS0, qidx);
	if (((fifo_state >> 62) & 0x03) == 0x3)
		nicvf_queue_reg_write(nic, NIC_QSET_RBDR_0_1_CFG,
				      qidx, NICVF_RBDR_RESET);

	/* Disable RBDR */
	nicvf_queue_reg_write(nic, NIC_QSET_RBDR_0_1_CFG, qidx, 0);
	if (nicvf_poll_reg(nic, qidx, NIC_QSET_RBDR_0_1_STATUS0, 62, 2, 0x00))
		return;
	while (1) {
		tmp = nicvf_queue_reg_read(nic,
					   NIC_QSET_RBDR_0_1_PREFETCH_STATUS,
					   qidx);
		if ((tmp & 0xFFFFFFFF) == ((tmp >> 32) & 0xFFFFFFFF))
			break;
		usleep_range(1000, 2000);
		timeout--;
		if (!timeout) {
			netdev_err(nic->netdev,
				   "Failed polling on prefetch status\n");
			return;
		}
	}
	nicvf_queue_reg_write(nic, NIC_QSET_RBDR_0_1_CFG,
			      qidx, NICVF_RBDR_RESET);

	if (nicvf_poll_reg(nic, qidx, NIC_QSET_RBDR_0_1_STATUS0, 62, 2, 0x02))
		return;
	nicvf_queue_reg_write(nic, NIC_QSET_RBDR_0_1_CFG, qidx, 0x00);
	if (nicvf_poll_reg(nic, qidx, NIC_QSET_RBDR_0_1_STATUS0, 62, 2, 0x00))
		return;
}