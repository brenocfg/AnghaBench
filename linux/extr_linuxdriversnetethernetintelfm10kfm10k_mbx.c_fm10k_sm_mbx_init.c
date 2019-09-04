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
struct fm10k_msg_data {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  register_handlers; int /*<<< orphan*/  process; int /*<<< orphan*/  enqueue_tx; int /*<<< orphan*/  tx_complete; int /*<<< orphan*/  tx_ready; int /*<<< orphan*/  rx_ready; int /*<<< orphan*/  disconnect; int /*<<< orphan*/  connect; } ;
struct fm10k_mbx_info {TYPE_1__ ops; int /*<<< orphan*/ * buffer; int /*<<< orphan*/  rx; int /*<<< orphan*/  tx; int /*<<< orphan*/  mbmem_len; int /*<<< orphan*/  max_size; int /*<<< orphan*/  udelay; scalar_t__ timeout; struct fm10k_msg_data const* msg_data; int /*<<< orphan*/  state; int /*<<< orphan*/  mbmem_reg; int /*<<< orphan*/  mbx_reg; } ;
struct fm10k_hw {int dummy; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  FM10K_ERR_PARAM ; 
 int /*<<< orphan*/  FM10K_GMBX ; 
 int /*<<< orphan*/  FM10K_MBMEM_PF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FM10K_MBMEM_PF_XOR ; 
 int /*<<< orphan*/  FM10K_MBX_INIT_DELAY ; 
 int /*<<< orphan*/  FM10K_MBX_MSG_MAX_SIZE ; 
 size_t FM10K_MBX_RX_BUFFER_SIZE ; 
 size_t FM10K_MBX_TX_BUFFER_SIZE ; 
 int /*<<< orphan*/  FM10K_STATE_CLOSED ; 
 int /*<<< orphan*/  fm10k_fifo_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  fm10k_mbx_enqueue_tx ; 
 int /*<<< orphan*/  fm10k_mbx_register_handlers ; 
 int /*<<< orphan*/  fm10k_mbx_rx_ready ; 
 int /*<<< orphan*/  fm10k_mbx_tx_complete ; 
 int /*<<< orphan*/  fm10k_mbx_tx_ready ; 
 scalar_t__ fm10k_mbx_validate_handlers (struct fm10k_msg_data const*) ; 
 int /*<<< orphan*/  fm10k_sm_mbx_connect ; 
 int /*<<< orphan*/  fm10k_sm_mbx_disconnect ; 
 int /*<<< orphan*/  fm10k_sm_mbx_process ; 

s32 fm10k_sm_mbx_init(struct fm10k_hw *hw, struct fm10k_mbx_info *mbx,
		      const struct fm10k_msg_data *msg_data)
{
	mbx->mbx_reg = FM10K_GMBX;
	mbx->mbmem_reg = FM10K_MBMEM_PF(0);

	/* start out in closed state */
	mbx->state = FM10K_STATE_CLOSED;

	/* validate layout of handlers before assigning them */
	if (fm10k_mbx_validate_handlers(msg_data))
		return FM10K_ERR_PARAM;

	/* initialize the message handlers */
	mbx->msg_data = msg_data;

	/* start mailbox as timed out and let the reset_hw call
	 * set the timeout value to begin communications
	 */
	mbx->timeout = 0;
	mbx->udelay = FM10K_MBX_INIT_DELAY;

	/* Split buffer for use by Tx/Rx FIFOs */
	mbx->max_size = FM10K_MBX_MSG_MAX_SIZE;
	mbx->mbmem_len = FM10K_MBMEM_PF_XOR;

	/* initialize the FIFOs, sizes are in 4 byte increments */
	fm10k_fifo_init(&mbx->tx, mbx->buffer, FM10K_MBX_TX_BUFFER_SIZE);
	fm10k_fifo_init(&mbx->rx, &mbx->buffer[FM10K_MBX_TX_BUFFER_SIZE],
			FM10K_MBX_RX_BUFFER_SIZE);

	/* initialize function pointers */
	mbx->ops.connect = fm10k_sm_mbx_connect;
	mbx->ops.disconnect = fm10k_sm_mbx_disconnect;
	mbx->ops.rx_ready = fm10k_mbx_rx_ready;
	mbx->ops.tx_ready = fm10k_mbx_tx_ready;
	mbx->ops.tx_complete = fm10k_mbx_tx_complete;
	mbx->ops.enqueue_tx = fm10k_mbx_enqueue_tx;
	mbx->ops.process = fm10k_sm_mbx_process;
	mbx->ops.register_handlers = fm10k_mbx_register_handlers;

	return 0;
}