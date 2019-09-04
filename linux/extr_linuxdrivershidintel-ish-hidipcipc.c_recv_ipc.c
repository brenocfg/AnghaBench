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
typedef  int uint32_t ;
struct ishtp_device {int recvd_hw_ready; int /*<<< orphan*/  wait_hw_ready; int /*<<< orphan*/  resume_wait; int /*<<< orphan*/  resume_flag; int /*<<< orphan*/  suspend_wait; int /*<<< orphan*/  suspend_flag; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int IPC_HEADER_GET_MNG_CMD (int) ; 
#define  MNG_RESET_NOTIFY 130 
#define  MNG_RESET_NOTIFY_ACK 129 
#define  MNG_RX_CMPL_INDICATION 128 
 int /*<<< orphan*/  fw_reset_work ; 
 int /*<<< orphan*/  fw_reset_work_fn ; 
 struct ishtp_device* ishtp_dev ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_ipc_from_queue (struct ishtp_device*) ; 

__attribute__((used)) static void	recv_ipc(struct ishtp_device *dev, uint32_t doorbell_val)
{
	uint32_t	mng_cmd;

	mng_cmd = IPC_HEADER_GET_MNG_CMD(doorbell_val);

	switch (mng_cmd) {
	default:
		break;

	case MNG_RX_CMPL_INDICATION:
		if (dev->suspend_flag) {
			dev->suspend_flag = 0;
			wake_up_interruptible(&dev->suspend_wait);
		}
		if (dev->resume_flag) {
			dev->resume_flag = 0;
			wake_up_interruptible(&dev->resume_wait);
		}

		write_ipc_from_queue(dev);
		break;

	case MNG_RESET_NOTIFY:
		if (!ishtp_dev) {
			ishtp_dev = dev;
			INIT_WORK(&fw_reset_work, fw_reset_work_fn);
		}
		schedule_work(&fw_reset_work);
		break;

	case MNG_RESET_NOTIFY_ACK:
		dev->recvd_hw_ready = 1;
		wake_up_interruptible(&dev->wait_hw_ready);
		break;
	}
}