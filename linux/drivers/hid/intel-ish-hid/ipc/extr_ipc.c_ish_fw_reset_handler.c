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
struct ishtp_device {int /*<<< orphan*/  devc; int /*<<< orphan*/  wr_processing_spinlock; int /*<<< orphan*/  wr_free_list; int /*<<< orphan*/  wr_processing_list; } ;

/* Variables and functions */
 int ENODEV ; 
 int EPIPE ; 
 int /*<<< orphan*/  IPC_REG_ISH2HOST_MSG ; 
 int /*<<< orphan*/  MNG_RESET_NOTIFY_ACK ; 
 int /*<<< orphan*/  TIMEOUT_FOR_FW_RDY_MS ; 
 int /*<<< orphan*/  TIMEOUT_FOR_INPUT_RDY_MS ; 
 int /*<<< orphan*/  TIME_SLICE_FOR_FW_RDY_MS ; 
 int /*<<< orphan*/  TIME_SLICE_FOR_INPUT_RDY_MS ; 
 int /*<<< orphan*/  WAIT_FOR_FW_RDY ; 
 int /*<<< orphan*/  WAIT_FOR_INPUT_RDY ; 
 int _ish_read_fw_sts_reg (struct ishtp_device*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ipc_send_mng_msg (struct ishtp_device*,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  ish_is_input_ready (struct ishtp_device*) ; 
 int ish_reg_read (struct ishtp_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ish_set_host_rdy (struct ishtp_device*) ; 
 int /*<<< orphan*/  ishtp_fw_is_ready (struct ishtp_device*) ; 
 int /*<<< orphan*/  ishtp_reset_handler (struct ishtp_device*) ; 
 int /*<<< orphan*/  list_splice_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  timed_wait_for_timeout (struct ishtp_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ish_fw_reset_handler(struct ishtp_device *dev)
{
	uint32_t	reset_id;
	unsigned long	flags;

	/* Read reset ID */
	reset_id = ish_reg_read(dev, IPC_REG_ISH2HOST_MSG) & 0xFFFF;

	/* Clear IPC output queue */
	spin_lock_irqsave(&dev->wr_processing_spinlock, flags);
	list_splice_init(&dev->wr_processing_list, &dev->wr_free_list);
	spin_unlock_irqrestore(&dev->wr_processing_spinlock, flags);

	/* ISHTP notification in IPC_RESET */
	ishtp_reset_handler(dev);

	if (!ish_is_input_ready(dev))
		timed_wait_for_timeout(dev, WAIT_FOR_INPUT_RDY,
			TIME_SLICE_FOR_INPUT_RDY_MS, TIMEOUT_FOR_INPUT_RDY_MS);

	/* ISH FW is dead */
	if (!ish_is_input_ready(dev))
		return	-EPIPE;
	/*
	 * Set HOST2ISH.ILUP. Apparently we need this BEFORE sending
	 * RESET_NOTIFY_ACK - FW will be checking for it
	 */
	ish_set_host_rdy(dev);
	/* Send RESET_NOTIFY_ACK (with reset_id) */
	ipc_send_mng_msg(dev, MNG_RESET_NOTIFY_ACK, &reset_id,
			 sizeof(uint32_t));

	/* Wait for ISH FW'es ILUP and ISHTP_READY */
	timed_wait_for_timeout(dev, WAIT_FOR_FW_RDY,
			TIME_SLICE_FOR_FW_RDY_MS, TIMEOUT_FOR_FW_RDY_MS);
	if (!ishtp_fw_is_ready(dev)) {
		/* ISH FW is dead */
		uint32_t	ish_status;

		ish_status = _ish_read_fw_sts_reg(dev);
		dev_err(dev->devc,
			"[ishtp-ish]: completed reset, ISH is dead (FWSTS = %08X)\n",
			ish_status);
		return -ENODEV;
	}
	return	0;
}