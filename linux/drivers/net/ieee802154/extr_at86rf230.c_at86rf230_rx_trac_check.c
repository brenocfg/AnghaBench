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
typedef  int u8 ;
struct TYPE_5__ {int len; } ;
struct TYPE_6__ {int /*<<< orphan*/  complete; } ;
struct at86rf230_state_change {int* buf; TYPE_2__ trx; TYPE_3__ msg; struct at86rf230_local* lp; } ;
struct TYPE_4__ {int /*<<< orphan*/  invalid; int /*<<< orphan*/  success_wait_for_ack; int /*<<< orphan*/  success; } ;
struct at86rf230_local {int /*<<< orphan*/  spi; TYPE_1__ trac; } ;

/* Variables and functions */
 int AT86RF2XX_MAX_BUF ; 
 int CMD_FB ; 
 int /*<<< orphan*/  CONFIG_IEEE802154_AT86RF230_DEBUGFS ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
#define  TRAC_INVALID 130 
 int TRAC_MASK (int) ; 
#define  TRAC_SUCCESS 129 
#define  TRAC_SUCCESS_WAIT_FOR_ACK 128 
 int /*<<< orphan*/  WARN_ONCE (int,char*,int) ; 
 int /*<<< orphan*/  at86rf230_async_error (struct at86rf230_local*,struct at86rf230_state_change*,int) ; 
 int /*<<< orphan*/  at86rf230_rx_read_frame_complete ; 
 int spi_async (int /*<<< orphan*/ ,TYPE_3__*) ; 

__attribute__((used)) static void
at86rf230_rx_trac_check(void *context)
{
	struct at86rf230_state_change *ctx = context;
	struct at86rf230_local *lp = ctx->lp;
	u8 *buf = ctx->buf;
	int rc;

	if (IS_ENABLED(CONFIG_IEEE802154_AT86RF230_DEBUGFS)) {
		u8 trac = TRAC_MASK(buf[1]);

		switch (trac) {
		case TRAC_SUCCESS:
			lp->trac.success++;
			break;
		case TRAC_SUCCESS_WAIT_FOR_ACK:
			lp->trac.success_wait_for_ack++;
			break;
		case TRAC_INVALID:
			lp->trac.invalid++;
			break;
		default:
			WARN_ONCE(1, "received rx trac status %d\n", trac);
			break;
		}
	}

	buf[0] = CMD_FB;
	ctx->trx.len = AT86RF2XX_MAX_BUF;
	ctx->msg.complete = at86rf230_rx_read_frame_complete;
	rc = spi_async(lp->spi, &ctx->msg);
	if (rc) {
		ctx->trx.len = 2;
		at86rf230_async_error(lp, ctx, rc);
	}
}