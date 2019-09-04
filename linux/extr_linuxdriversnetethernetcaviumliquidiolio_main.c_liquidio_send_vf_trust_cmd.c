#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct octeon_soft_command {int wait_time; struct octeon_soft_command* callback_arg; int /*<<< orphan*/  callback; int /*<<< orphan*/  iq_no; scalar_t__ ctxptr; } ;
struct octeon_device {int dummy; } ;
struct lio_trusted_vf_ctx {int status; int /*<<< orphan*/  complete; } ;
struct TYPE_6__ {TYPE_2__* txpciq; } ;
struct lio {TYPE_3__ linfo; struct octeon_device* oct_dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  q_no; } ;
struct TYPE_5__ {TYPE_1__ s; } ;

/* Variables and functions */
 int IQ_SEND_FAILED ; 
 int /*<<< orphan*/  OPCODE_NIC ; 
 int /*<<< orphan*/  OPCODE_NIC_SET_TRUSTED_VF ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 struct octeon_soft_command* octeon_alloc_soft_command (struct octeon_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  octeon_free_soft_command (struct octeon_device*,struct octeon_soft_command*) ; 
 int /*<<< orphan*/  octeon_prepare_soft_command (struct octeon_device*,struct octeon_soft_command*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int octeon_send_soft_command (struct octeon_device*,struct octeon_soft_command*) ; 
 int /*<<< orphan*/  trusted_vf_callback ; 
 scalar_t__ wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int liquidio_send_vf_trust_cmd(struct lio *lio, int vfidx, bool trusted)
{
	struct octeon_device *oct = lio->oct_dev;
	struct lio_trusted_vf_ctx *ctx;
	struct octeon_soft_command *sc;
	int ctx_size, retval;

	ctx_size = sizeof(struct lio_trusted_vf_ctx);
	sc = octeon_alloc_soft_command(oct, 0, 0, ctx_size);

	ctx  = (struct lio_trusted_vf_ctx *)sc->ctxptr;
	init_completion(&ctx->complete);

	sc->iq_no = lio->linfo.txpciq[0].s.q_no;

	/* vfidx is 0 based, but vf_num (param1) is 1 based */
	octeon_prepare_soft_command(oct, sc, OPCODE_NIC,
				    OPCODE_NIC_SET_TRUSTED_VF, 0, vfidx + 1,
				    trusted);

	sc->callback = trusted_vf_callback;
	sc->callback_arg = sc;
	sc->wait_time = 1000;

	retval = octeon_send_soft_command(oct, sc);
	if (retval == IQ_SEND_FAILED) {
		retval = -1;
	} else {
		/* Wait for response or timeout */
		if (wait_for_completion_timeout(&ctx->complete,
						msecs_to_jiffies(2000)))
			retval = ctx->status;
		else
			retval = -1;
	}

	octeon_free_soft_command(oct, sc);

	return retval;
}