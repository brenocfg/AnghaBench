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
typedef  int u16 ;
struct nicpf {TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  NIC_PF_SW_SYNC_RX ; 
 int /*<<< orphan*/  NIC_PF_SW_SYNC_RX_DONE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int nic_reg_read (struct nicpf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nic_reg_write (struct nicpf*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int nic_rcv_queue_sw_sync(struct nicpf *nic)
{
	u16 timeout = ~0x00;

	nic_reg_write(nic, NIC_PF_SW_SYNC_RX, 0x01);
	/* Wait till sync cycle is finished */
	while (timeout) {
		if (nic_reg_read(nic, NIC_PF_SW_SYNC_RX_DONE) & 0x1)
			break;
		timeout--;
	}
	nic_reg_write(nic, NIC_PF_SW_SYNC_RX, 0x00);
	if (!timeout) {
		dev_err(&nic->pdev->dev, "Receive queue software sync failed");
		return 1;
	}
	return 0;
}