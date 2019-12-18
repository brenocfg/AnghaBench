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
struct TYPE_2__ {int /*<<< orphan*/  done; int /*<<< orphan*/  wait; } ;
struct request_context {int state; TYPE_1__ done; } ;
struct ezusb_priv {int dummy; } ;

/* Variables and functions */
 int DEF_TIMEOUT ; 
#define  EZUSB_CTX_QUEUED 131 
#define  EZUSB_CTX_REQ_COMPLETE 130 
#define  EZUSB_CTX_REQ_SUBMITTED 129 
#define  EZUSB_CTX_RESP_RECEIVED 128 
 int HZ ; 
 int /*<<< orphan*/  in_softirq () ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  wait_event_interruptible (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ezusb_req_ctx_wait(struct ezusb_priv *upriv,
			       struct request_context *ctx)
{
	switch (ctx->state) {
	case EZUSB_CTX_QUEUED:
	case EZUSB_CTX_REQ_SUBMITTED:
	case EZUSB_CTX_REQ_COMPLETE:
	case EZUSB_CTX_RESP_RECEIVED:
		if (in_softirq()) {
			/* If we get called from a timer, timeout timers don't
			 * get the chance to run themselves. So we make sure
			 * that we don't sleep for ever */
			int msecs = DEF_TIMEOUT * (1000 / HZ);
			while (!ctx->done.done && msecs--)
				udelay(1000);
		} else {
			wait_event_interruptible(ctx->done.wait,
						 ctx->done.done);
		}
		break;
	default:
		/* Done or failed - nothing to wait for */
		break;
	}
}