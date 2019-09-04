#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int param1; int /*<<< orphan*/  cmd; } ;
union octnet_cmd {TYPE_1__ s; scalar_t__ u64; } ;
typedef  int /*<<< orphan*/  u64 ;
struct octeon_soft_command {int wait_time; struct octeon_soft_command* callback_arg; int /*<<< orphan*/  callback; int /*<<< orphan*/  iq_no; scalar_t__ ctxptr; scalar_t__ virtdptr; } ;
struct octeon_device {TYPE_5__* props; } ;
struct liquidio_rx_ctl_context {int /*<<< orphan*/  cond; int /*<<< orphan*/  wc; int /*<<< orphan*/  octeon_id; } ;
struct TYPE_9__ {TYPE_3__* txpciq; } ;
struct lio {size_t ifidx; int /*<<< orphan*/  netdev; TYPE_4__ linfo; scalar_t__ oct_dev; } ;
struct TYPE_10__ {int rx_on; } ;
struct TYPE_7__ {int /*<<< orphan*/  q_no; } ;
struct TYPE_8__ {TYPE_2__ s; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINTR ; 
 int IQ_SEND_FAILED ; 
 int /*<<< orphan*/  OCTNET_CMD_RX_CTL ; 
 int OCTNET_CMD_SIZE ; 
 int /*<<< orphan*/  OPCODE_NIC ; 
 int /*<<< orphan*/  OPCODE_NIC_CMD ; 
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lio_get_device_id (struct octeon_device*) ; 
 int /*<<< orphan*/  netif_info (struct lio*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ octeon_alloc_soft_command (struct octeon_device*,int,int,int) ; 
 int /*<<< orphan*/  octeon_free_soft_command (struct octeon_device*,struct octeon_soft_command*) ; 
 int /*<<< orphan*/  octeon_prepare_soft_command (struct octeon_device*,struct octeon_soft_command*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int octeon_send_soft_command (struct octeon_device*,struct octeon_soft_command*) ; 
 int /*<<< orphan*/  octeon_swap_8B_data (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rx_ctl_callback ; 
 int /*<<< orphan*/  rx_err ; 
 int /*<<< orphan*/  sleep_cond (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void send_rx_ctrl_cmd(struct lio *lio, int start_stop)
{
	struct octeon_soft_command *sc;
	struct liquidio_rx_ctl_context *ctx;
	union octnet_cmd *ncmd;
	int ctx_size = sizeof(struct liquidio_rx_ctl_context);
	struct octeon_device *oct = (struct octeon_device *)lio->oct_dev;
	int retval;

	if (oct->props[lio->ifidx].rx_on == start_stop)
		return;

	sc = (struct octeon_soft_command *)
		octeon_alloc_soft_command(oct, OCTNET_CMD_SIZE,
					  16, ctx_size);

	ncmd = (union octnet_cmd *)sc->virtdptr;
	ctx  = (struct liquidio_rx_ctl_context *)sc->ctxptr;

	WRITE_ONCE(ctx->cond, 0);
	ctx->octeon_id = lio_get_device_id(oct);
	init_waitqueue_head(&ctx->wc);

	ncmd->u64 = 0;
	ncmd->s.cmd = OCTNET_CMD_RX_CTL;
	ncmd->s.param1 = start_stop;

	octeon_swap_8B_data((u64 *)ncmd, (OCTNET_CMD_SIZE >> 3));

	sc->iq_no = lio->linfo.txpciq[0].s.q_no;

	octeon_prepare_soft_command(oct, sc, OPCODE_NIC,
				    OPCODE_NIC_CMD, 0, 0, 0);

	sc->callback = rx_ctl_callback;
	sc->callback_arg = sc;
	sc->wait_time = 5000;

	retval = octeon_send_soft_command(oct, sc);
	if (retval == IQ_SEND_FAILED) {
		netif_info(lio, rx_err, lio->netdev, "Failed to send RX Control message\n");
	} else {
		/* Sleep on a wait queue till the cond flag indicates that the
		 * response arrived or timed-out.
		 */
		if (sleep_cond(&ctx->wc, &ctx->cond) == -EINTR)
			return;
		oct->props[lio->ifidx].rx_on = start_stop;
	}

	octeon_free_soft_command(oct, sc);
}