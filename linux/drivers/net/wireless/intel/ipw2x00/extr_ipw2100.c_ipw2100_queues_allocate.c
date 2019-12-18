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
struct ipw2100_priv {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ ipw2100_msg_allocate (struct ipw2100_priv*) ; 
 int /*<<< orphan*/  ipw2100_msg_free (struct ipw2100_priv*) ; 
 scalar_t__ ipw2100_rx_allocate (struct ipw2100_priv*) ; 
 int /*<<< orphan*/  ipw2100_rx_free (struct ipw2100_priv*) ; 
 scalar_t__ ipw2100_tx_allocate (struct ipw2100_priv*) ; 
 int /*<<< orphan*/  ipw2100_tx_free (struct ipw2100_priv*) ; 

__attribute__((used)) static int ipw2100_queues_allocate(struct ipw2100_priv *priv)
{
	if (ipw2100_tx_allocate(priv) ||
	    ipw2100_rx_allocate(priv) || ipw2100_msg_allocate(priv))
		goto fail;

	return 0;

      fail:
	ipw2100_tx_free(priv);
	ipw2100_rx_free(priv);
	ipw2100_msg_free(priv);
	return -ENOMEM;
}