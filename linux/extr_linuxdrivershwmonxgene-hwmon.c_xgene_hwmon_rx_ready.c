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
struct xgene_hwmon_dev {int /*<<< orphan*/  kfifo_lock; int /*<<< orphan*/  async_msg_fifo; int /*<<< orphan*/  resp_pending; int /*<<< orphan*/  hwmon_dev; } ;
struct slimpro_resp_msg {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ IS_ERR_OR_NULL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfifo_in_spinlocked (int /*<<< orphan*/ *,void*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int xgene_hwmon_rx_ready(struct xgene_hwmon_dev *ctx, void *msg)
{
	if (IS_ERR_OR_NULL(ctx->hwmon_dev) && !ctx->resp_pending) {
		/* Enqueue to the FIFO */
		kfifo_in_spinlocked(&ctx->async_msg_fifo, msg,
				    sizeof(struct slimpro_resp_msg),
				    &ctx->kfifo_lock);
		return -ENODEV;
	}

	return 0;
}