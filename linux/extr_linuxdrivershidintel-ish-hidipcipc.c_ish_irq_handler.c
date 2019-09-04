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
typedef  int /*<<< orphan*/  uint32_t ;
struct ishtp_device {scalar_t__ dev_state; int /*<<< orphan*/  ipc_rx_bytes_cnt; int /*<<< orphan*/  ipc_rx_cnt; int /*<<< orphan*/  devc; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 scalar_t__ IPC_HEADER_GET_LENGTH (int /*<<< orphan*/ ) ; 
 int IPC_HEADER_GET_PROTOCOL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IPC_IS_BUSY (int /*<<< orphan*/ ) ; 
 scalar_t__ IPC_PAYLOAD_SIZE ; 
#define  IPC_PROTOCOL_ISHTP 129 
#define  IPC_PROTOCOL_MNG 128 
 int /*<<< orphan*/  IPC_REG_ISH2HOST_DRBL ; 
 int /*<<< orphan*/  IPC_REG_ISH_HOST_FWSTS ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 scalar_t__ ISHTP_DEV_DISABLED ; 
 int check_generated_interrupt (struct ishtp_device*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  ish_reg_read (struct ishtp_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ish_reg_write (struct ishtp_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ishtp_recv (struct ishtp_device*) ; 
 int /*<<< orphan*/  recv_ipc (struct ishtp_device*,int /*<<< orphan*/ ) ; 

irqreturn_t ish_irq_handler(int irq, void *dev_id)
{
	struct ishtp_device	*dev = dev_id;
	uint32_t	doorbell_val;
	bool	interrupt_generated;

	/* Check that it's interrupt from ISH (may be shared) */
	interrupt_generated = check_generated_interrupt(dev);

	if (!interrupt_generated)
		return IRQ_NONE;

	doorbell_val = ish_reg_read(dev, IPC_REG_ISH2HOST_DRBL);
	if (!IPC_IS_BUSY(doorbell_val))
		return IRQ_HANDLED;

	if (dev->dev_state == ISHTP_DEV_DISABLED)
		return	IRQ_HANDLED;

	/* Sanity check: IPC dgram length in header */
	if (IPC_HEADER_GET_LENGTH(doorbell_val) > IPC_PAYLOAD_SIZE) {
		dev_err(dev->devc,
			"IPC hdr - bad length: %u; dropped\n",
			(unsigned int)IPC_HEADER_GET_LENGTH(doorbell_val));
		goto	eoi;
	}

	switch (IPC_HEADER_GET_PROTOCOL(doorbell_val)) {
	default:
		break;
	case IPC_PROTOCOL_MNG:
		recv_ipc(dev, doorbell_val);
		break;
	case IPC_PROTOCOL_ISHTP:
		ishtp_recv(dev);
		break;
	}

eoi:
	/* Update IPC counters */
	++dev->ipc_rx_cnt;
	dev->ipc_rx_bytes_cnt += IPC_HEADER_GET_LENGTH(doorbell_val);

	ish_reg_write(dev, IPC_REG_ISH2HOST_DRBL, 0);
	/* Flush write to doorbell */
	ish_reg_read(dev, IPC_REG_ISH_HOST_FWSTS);

	return	IRQ_HANDLED;
}