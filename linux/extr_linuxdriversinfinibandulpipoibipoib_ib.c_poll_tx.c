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
struct ipoib_dev_priv {struct ib_wc* send_wc; int /*<<< orphan*/  dev; int /*<<< orphan*/  send_cq; } ;
struct ib_wc {int wr_id; } ;

/* Variables and functions */
 int IPOIB_OP_CM ; 
 int MAX_SEND_CQE ; 
 int ib_poll_cq (int /*<<< orphan*/ ,int,struct ib_wc*) ; 
 int /*<<< orphan*/  ipoib_cm_handle_tx_wc (int /*<<< orphan*/ ,struct ib_wc*) ; 
 int /*<<< orphan*/  ipoib_ib_handle_tx_wc (int /*<<< orphan*/ ,struct ib_wc*) ; 

__attribute__((used)) static int poll_tx(struct ipoib_dev_priv *priv)
{
	int n, i;
	struct ib_wc *wc;

	n = ib_poll_cq(priv->send_cq, MAX_SEND_CQE, priv->send_wc);
	for (i = 0; i < n; ++i) {
		wc = priv->send_wc + i;
		if (wc->wr_id & IPOIB_OP_CM)
			ipoib_cm_handle_tx_wc(priv->dev, priv->send_wc + i);
		else
			ipoib_ib_handle_tx_wc(priv->dev, priv->send_wc + i);
	}
	return n == MAX_SEND_CQE;
}