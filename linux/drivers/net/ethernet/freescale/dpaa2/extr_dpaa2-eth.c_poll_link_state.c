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
struct dpaa2_eth_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPAA2_ETH_LINK_STATE_REFRESH ; 
 int /*<<< orphan*/  kthread_should_stop () ; 
 int link_state_update (struct dpaa2_eth_priv*) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int poll_link_state(void *arg)
{
	struct dpaa2_eth_priv *priv = (struct dpaa2_eth_priv *)arg;
	int err;

	while (!kthread_should_stop()) {
		err = link_state_update(priv);
		if (unlikely(err))
			return err;

		msleep(DPAA2_ETH_LINK_STATE_REFRESH);
	}

	return 0;
}