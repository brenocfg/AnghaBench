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
struct usbhs_priv {int dummy; } ;
struct usbhs_pkt {int /*<<< orphan*/  (* done ) (struct usbhs_priv*,struct usbhs_pkt*) ;TYPE_1__* handler; } ;
struct usbhs_pipe {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int (* prepare ) (struct usbhs_pkt*,int*) ;int (* try_run ) (struct usbhs_pkt*,int*) ;int (* dma_done ) (struct usbhs_pkt*,int*) ;} ;

/* Variables and functions */
#define  USBHSF_PKT_DMA_DONE 130 
#define  USBHSF_PKT_PREPARE 129 
#define  USBHSF_PKT_TRY_RUN 128 
 int /*<<< orphan*/  __usbhsf_pkt_del (struct usbhs_pkt*) ; 
 struct usbhs_pkt* __usbhsf_pkt_get (struct usbhs_pipe*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 scalar_t__ likely (int (*) (struct usbhs_pkt*,int*)) ; 
 int /*<<< orphan*/  stub1 (struct usbhs_priv*,struct usbhs_pkt*) ; 
 int /*<<< orphan*/  usbhs_lock (struct usbhs_priv*,unsigned long) ; 
 struct usbhs_priv* usbhs_pipe_to_priv (struct usbhs_pipe*) ; 
 int /*<<< orphan*/  usbhs_pkt_start (struct usbhs_pipe*) ; 
 struct device* usbhs_priv_to_dev (struct usbhs_priv*) ; 
 int /*<<< orphan*/  usbhs_unlock (struct usbhs_priv*,unsigned long) ; 

__attribute__((used)) static int usbhsf_pkt_handler(struct usbhs_pipe *pipe, int type)
{
	struct usbhs_priv *priv = usbhs_pipe_to_priv(pipe);
	struct usbhs_pkt *pkt;
	struct device *dev = usbhs_priv_to_dev(priv);
	int (*func)(struct usbhs_pkt *pkt, int *is_done);
	unsigned long flags;
	int ret = 0;
	int is_done = 0;

	/********************  spin lock ********************/
	usbhs_lock(priv, flags);

	pkt = __usbhsf_pkt_get(pipe);
	if (!pkt)
		goto __usbhs_pkt_handler_end;

	switch (type) {
	case USBHSF_PKT_PREPARE:
		func = pkt->handler->prepare;
		break;
	case USBHSF_PKT_TRY_RUN:
		func = pkt->handler->try_run;
		break;
	case USBHSF_PKT_DMA_DONE:
		func = pkt->handler->dma_done;
		break;
	default:
		dev_err(dev, "unknown pkt handler\n");
		goto __usbhs_pkt_handler_end;
	}

	if (likely(func))
		ret = func(pkt, &is_done);

	if (is_done)
		__usbhsf_pkt_del(pkt);

__usbhs_pkt_handler_end:
	usbhs_unlock(priv, flags);
	/********************  spin unlock ******************/

	if (is_done) {
		pkt->done(priv, pkt);
		usbhs_pkt_start(pipe);
	}

	return ret;
}