#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct octeon_soft_command {int wait_time; struct octeon_soft_command* callback_arg; int /*<<< orphan*/  callback; int /*<<< orphan*/  iq_no; scalar_t__ ctxptr; scalar_t__ virtrptr; } ;
struct octeon_device {TYPE_4__* pci_dev; } ;
struct oct_intrmod_resp {int /*<<< orphan*/  intrmod; scalar_t__ status; int /*<<< orphan*/  cond; int /*<<< orphan*/  wc; int /*<<< orphan*/  octeon_id; } ;
struct oct_intrmod_context {int /*<<< orphan*/  intrmod; scalar_t__ status; int /*<<< orphan*/  cond; int /*<<< orphan*/  wc; int /*<<< orphan*/  octeon_id; } ;
struct oct_intrmod_cfg {int dummy; } ;
struct TYPE_7__ {TYPE_2__* txpciq; } ;
struct lio {TYPE_3__ linfo; struct octeon_device* oct_dev; } ;
struct TYPE_8__ {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  q_no; } ;
struct TYPE_6__ {TYPE_1__ s; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINTR ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int IQ_SEND_FAILED ; 
 int /*<<< orphan*/  OPCODE_NIC ; 
 int /*<<< orphan*/  OPCODE_NIC_INTRMOD_PARAMS ; 
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lio_get_device_id (struct octeon_device*) ; 
 int /*<<< orphan*/  memcpy (struct oct_intrmod_cfg*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (struct oct_intrmod_resp*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ octeon_alloc_soft_command (struct octeon_device*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  octeon_free_soft_command (struct octeon_device*,struct octeon_soft_command*) ; 
 int /*<<< orphan*/  octeon_prepare_soft_command (struct octeon_device*,struct octeon_soft_command*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int octeon_send_soft_command (struct octeon_device*,struct octeon_soft_command*) ; 
 int /*<<< orphan*/  octeon_swap_8B_data (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  octnet_intrmod_callback ; 
 int /*<<< orphan*/  sleep_cond (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int octnet_get_intrmod_cfg(struct lio *lio,
				  struct oct_intrmod_cfg *intr_cfg)
{
	struct octeon_soft_command *sc;
	struct oct_intrmod_context *ctx;
	struct oct_intrmod_resp *resp;
	int retval;
	struct octeon_device *oct_dev = lio->oct_dev;

	/* Alloc soft command */
	sc = (struct octeon_soft_command *)
		octeon_alloc_soft_command(oct_dev,
					  0,
					  sizeof(struct oct_intrmod_resp),
					  sizeof(struct oct_intrmod_context));

	if (!sc)
		return -ENOMEM;

	resp = (struct oct_intrmod_resp *)sc->virtrptr;
	memset(resp, 0, sizeof(struct oct_intrmod_resp));

	ctx = (struct oct_intrmod_context *)sc->ctxptr;
	memset(ctx, 0, sizeof(struct oct_intrmod_context));
	WRITE_ONCE(ctx->cond, 0);
	ctx->octeon_id = lio_get_device_id(oct_dev);
	init_waitqueue_head(&ctx->wc);

	sc->iq_no = lio->linfo.txpciq[0].s.q_no;

	octeon_prepare_soft_command(oct_dev, sc, OPCODE_NIC,
				    OPCODE_NIC_INTRMOD_PARAMS, 0, 0, 0);

	sc->callback = octnet_intrmod_callback;
	sc->callback_arg = sc;
	sc->wait_time = 1000;

	retval = octeon_send_soft_command(oct_dev, sc);
	if (retval == IQ_SEND_FAILED) {
		octeon_free_soft_command(oct_dev, sc);
		return -EINVAL;
	}

	/* Sleep on a wait queue till the cond flag indicates that the
	 * response arrived or timed-out.
	 */
	if (sleep_cond(&ctx->wc, &ctx->cond) == -EINTR) {
		dev_err(&oct_dev->pci_dev->dev, "Wait interrupted\n");
		goto intrmod_info_wait_intr;
	}

	retval = ctx->status || resp->status;
	if (retval) {
		dev_err(&oct_dev->pci_dev->dev,
			"Get interrupt moderation parameters failed\n");
		goto intrmod_info_wait_fail;
	}

	octeon_swap_8B_data((u64 *)&resp->intrmod,
			    (sizeof(struct oct_intrmod_cfg)) / 8);
	memcpy(intr_cfg, &resp->intrmod, sizeof(struct oct_intrmod_cfg));
	octeon_free_soft_command(oct_dev, sc);

	return 0;

intrmod_info_wait_fail:

	octeon_free_soft_command(oct_dev, sc);

intrmod_info_wait_intr:

	return -ENODEV;
}