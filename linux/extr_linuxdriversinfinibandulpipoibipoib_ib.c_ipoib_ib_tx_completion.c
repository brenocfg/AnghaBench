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
struct ipoib_dev_priv {int /*<<< orphan*/  send_napi; } ;
struct ib_cq {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  napi_schedule (int /*<<< orphan*/ *) ; 

void ipoib_ib_tx_completion(struct ib_cq *cq, void *ctx_ptr)
{
	struct ipoib_dev_priv *priv = ctx_ptr;

	napi_schedule(&priv->send_napi);
}