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
struct mcba_usb_ctx {scalar_t__ ndx; int can; scalar_t__ dlc; } ;
struct mcba_priv {int /*<<< orphan*/  netdev; int /*<<< orphan*/  free_ctx_cnt; struct mcba_usb_ctx* tx_context; } ;
struct can_frame {scalar_t__ can_dlc; } ;

/* Variables and functions */
 scalar_t__ MCBA_CTX_FREE ; 
 int MCBA_MAX_TX_URBS ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_stop_queue (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct mcba_usb_ctx *mcba_usb_get_free_ctx(struct mcba_priv *priv,
							 struct can_frame *cf)
{
	int i = 0;
	struct mcba_usb_ctx *ctx = NULL;

	for (i = 0; i < MCBA_MAX_TX_URBS; i++) {
		if (priv->tx_context[i].ndx == MCBA_CTX_FREE) {
			ctx = &priv->tx_context[i];
			ctx->ndx = i;

			if (cf) {
				ctx->can = true;
				ctx->dlc = cf->can_dlc;
			} else {
				ctx->can = false;
				ctx->dlc = 0;
			}

			atomic_dec(&priv->free_ctx_cnt);
			break;
		}
	}

	if (!atomic_read(&priv->free_ctx_cnt))
		/* That was the last free ctx. Slow down tx path */
		netif_stop_queue(priv->netdev);

	return ctx;
}