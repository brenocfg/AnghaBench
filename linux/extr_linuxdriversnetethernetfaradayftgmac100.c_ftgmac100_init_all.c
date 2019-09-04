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
struct ftgmac100 {scalar_t__ base; int /*<<< orphan*/  netdev; int /*<<< orphan*/  napi; } ;

/* Variables and functions */
 int /*<<< orphan*/  FTGMAC100_INT_ALL ; 
 scalar_t__ FTGMAC100_OFFSET_IER ; 
 int ftgmac100_alloc_rx_buffers (struct ftgmac100*) ; 
 int /*<<< orphan*/  ftgmac100_config_pause (struct ftgmac100*) ; 
 int /*<<< orphan*/  ftgmac100_init_hw (struct ftgmac100*) ; 
 int /*<<< orphan*/  ftgmac100_init_rings (struct ftgmac100*) ; 
 int /*<<< orphan*/  ftgmac100_start_hw (struct ftgmac100*) ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_start_queue (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ftgmac100_init_all(struct ftgmac100 *priv, bool ignore_alloc_err)
{
	int err = 0;

	/* Re-init descriptors (adjust queue sizes) */
	ftgmac100_init_rings(priv);

	/* Realloc rx descriptors */
	err = ftgmac100_alloc_rx_buffers(priv);
	if (err && !ignore_alloc_err)
		return err;

	/* Reinit and restart HW */
	ftgmac100_init_hw(priv);
	ftgmac100_config_pause(priv);
	ftgmac100_start_hw(priv);

	/* Re-enable the device */
	napi_enable(&priv->napi);
	netif_start_queue(priv->netdev);

	/* Enable all interrupts */
	iowrite32(FTGMAC100_INT_ALL, priv->base + FTGMAC100_OFFSET_IER);

	return err;
}