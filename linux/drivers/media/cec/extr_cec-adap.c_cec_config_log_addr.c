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
struct cec_msg {int len; unsigned int* msg; int tx_status; } ;
struct cec_log_addrs {unsigned int* log_addr; int log_addr_mask; } ;
struct cec_adapter {int /*<<< orphan*/  phys_addr; int /*<<< orphan*/ * phys_addrs; TYPE_1__* ops; int /*<<< orphan*/  is_configuring; struct cec_log_addrs log_addrs; } ;
struct TYPE_2__ {int (* adap_log_addr ) (struct cec_adapter*,unsigned int) ;} ;

/* Variables and functions */
 int CEC_TX_STATUS_ABORTED ; 
 int CEC_TX_STATUS_NACK ; 
 int CEC_TX_STATUS_OK ; 
 int EINTR ; 
 scalar_t__ cec_has_log_addr (struct cec_adapter*,unsigned int) ; 
 int cec_transmit_msg_fh (struct cec_adapter*,struct cec_msg*,int /*<<< orphan*/ *,int) ; 
 int stub1 (struct cec_adapter*,unsigned int) ; 

__attribute__((used)) static int cec_config_log_addr(struct cec_adapter *adap,
			       unsigned int idx,
			       unsigned int log_addr)
{
	struct cec_log_addrs *las = &adap->log_addrs;
	struct cec_msg msg = { };
	const unsigned int max_retries = 2;
	unsigned int i;
	int err;

	if (cec_has_log_addr(adap, log_addr))
		return 0;

	/* Send poll message */
	msg.len = 1;
	msg.msg[0] = (log_addr << 4) | log_addr;

	for (i = 0; i < max_retries; i++) {
		err = cec_transmit_msg_fh(adap, &msg, NULL, true);

		/*
		 * While trying to poll the physical address was reset
		 * and the adapter was unconfigured, so bail out.
		 */
		if (!adap->is_configuring)
			return -EINTR;

		if (err)
			return err;

		/*
		 * The message was aborted due to a disconnect or
		 * unconfigure, just bail out.
		 */
		if (msg.tx_status & CEC_TX_STATUS_ABORTED)
			return -EINTR;
		if (msg.tx_status & CEC_TX_STATUS_OK)
			return 0;
		if (msg.tx_status & CEC_TX_STATUS_NACK)
			break;
		/*
		 * Retry up to max_retries times if the message was neither
		 * OKed or NACKed. This can happen due to e.g. a Lost
		 * Arbitration condition.
		 */
	}

	/*
	 * If we are unable to get an OK or a NACK after max_retries attempts
	 * (and note that each attempt already consists of four polls), then
	 * then we assume that something is really weird and that it is not a
	 * good idea to try and claim this logical address.
	 */
	if (i == max_retries)
		return 0;

	/*
	 * Message not acknowledged, so this logical
	 * address is free to use.
	 */
	err = adap->ops->adap_log_addr(adap, log_addr);
	if (err)
		return err;

	las->log_addr[idx] = log_addr;
	las->log_addr_mask |= 1 << log_addr;
	adap->phys_addrs[log_addr] = adap->phys_addr;
	return 1;
}